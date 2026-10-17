// SPDX-License-Identifier: GPL-2.0
/* Experimental boot-local wake-mask quirk; no automatic suspend. */
#include <linux/acpi.h>
#include <linux/dmi.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/string.h>

#define TARGET_GPE 0x02
static bool armed;
static bool marked;

static int __init fx607_gpe02_init(void)
{
	acpi_event_status flags;
	acpi_status status;
	acpi_handle handle;
	const char *board = dmi_get_system_info(DMI_BOARD_NAME);
	const char *bios = dmi_get_system_info(DMI_BIOS_VERSION);
	size_t board_len;

	if (!board || !bios ||
	    (strcmp(board, "FX607VJ") && strcmp(board, "FX607VUR")))
		return -ENODEV;
	board_len = strlen(board);
	if (strncmp(bios, board, board_len) || strcmp(bios + board_len, ".340"))
		return -ENODEV;
	if (ACPI_FAILURE(acpi_get_handle(NULL, "\\_GPE._L02", &handle)) ||
	    ACPI_FAILURE(acpi_get_handle(NULL, "\\_SB.PC00.LPCB.ECLV", &handle)))
		return -ENODEV;
	status = acpi_get_gpe_status(NULL, TARGET_GPE, &flags);
	if (ACPI_FAILURE(status))
		return -EIO;
	if (!(flags & ACPI_EVENT_FLAG_HAS_HANDLER) ||
	    (flags & ACPI_EVENT_FLAG_WAKE_ENABLED)) {
		pr_err("fx607_gpe02: unexpected baseline GPE status 0x%x; refusing change\n", flags);
		return -EBUSY;
	}

	/* Only add the capability flag if the exported API requires it. */
	status = acpi_set_gpe_wake_mask(NULL, TARGET_GPE, ACPI_GPE_ENABLE);
	if (status == AE_TYPE) {
		status = acpi_mark_gpe_for_wake(NULL, TARGET_GPE);
		if (ACPI_FAILURE(status))
			return -EIO;
		marked = true;
		status = acpi_set_gpe_wake_mask(NULL, TARGET_GPE, ACPI_GPE_ENABLE);
	}
	if (ACPI_FAILURE(status)) {
		pr_err("fx607_gpe02: cannot arm GPE02 (0x%x); capability_added=%d, reboot to fully restore\n",
		       status, marked);
		return -EIO;
	}
	armed = true;
	pr_info("fx607_gpe02: GPE02 wake mask armed; capability_added=%d; experimental boot-local quirk\n", marked);
	return 0;
}

static void __exit fx607_gpe02_exit(void)
{
	acpi_status status;

	if (!armed)
		return;
	status = acpi_set_gpe_wake_mask(NULL, TARGET_GPE, ACPI_GPE_DISABLE);
	pr_info("fx607_gpe02: wake mask cleared, status=0x%x; capability_added=%d; reboot for full baseline\n",
		status, marked);
}

module_init(fx607_gpe02_init);
module_exit(fx607_gpe02_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Experimental FX607VJ/FX607VUR BIOS 340 GPE02 wake-mask quirk");

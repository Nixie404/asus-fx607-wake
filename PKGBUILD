# Maintainer: Nixie404 <tudormares30@gmail.com>
pkgname=fx607-gpe02-dkms
pkgver=0.1.0
pkgrel=1
pkgdesc='Experimental ASUS FX607VJ BIOS 340 GPE02 lid wake workaround'
arch=('x86_64')
license=('GPL-2.0-only')
install=fx607-gpe02.install
depends=('dkms' 'systemd' 'kmod')
optdepends=('linux-headers: headers for the standard Arch kernel'
            'linux-lts-headers: headers for the Arch LTS kernel')
source=('fx607_gpe02.c' 'Makefile' 'dkms.conf' 'fx607-gpe02.service'
        'check-platform' 'README.md' 'LICENSE')
# Populated with real hashes by scripts/update-arch-checksums.py.
sha256sums=('b5d02170ac6c6c657181949164d0bc1513f72cb7f3a06a2e35d6effe28f26220'
            'a090a95bd3f767d0cfc6a29e4c9b711da544e93842946a69ecc087c15814333f'
            '849f81228660350fa9bc71123025943e0bea7fa7f82e28a57023953d2528fd7a'
            '692713b4259b4b4e19c857cf9d5c3c83765daf111ee117b3678a1ae4d9dca785'
            '607287a4bf9b05b1d8a461d11718781c64038d828183c385a195cf3392e6bd2d'
            'ed8d6c685e0637e3886488290cfc06e57a26a6585efcaae2a2b5b790b080cd1e'
            'edaef632cbb643e4e7a221717a6c441a4c1a7c918e6e4d56debc3d8739b233f6')

package() {
    install -Dm644 "$srcdir/fx607_gpe02.c" "$pkgdir/usr/src/fx607-gpe02-$pkgver/fx607_gpe02.c"
    install -Dm644 "$srcdir/Makefile" "$pkgdir/usr/src/fx607-gpe02-$pkgver/Makefile"
    install -Dm644 "$srcdir/dkms.conf" "$pkgdir/usr/src/fx607-gpe02-$pkgver/dkms.conf"
    install -Dm755 "$srcdir/check-platform" "$pkgdir/usr/lib/fx607-gpe02/check-platform"
    install -Dm644 "$srcdir/fx607-gpe02.service" "$pkgdir/usr/lib/systemd/system/fx607-gpe02.service"
    install -Dm644 "$srcdir/README.md" "$pkgdir/usr/share/doc/$pkgname/README.md"
    install -Dm644 "$srcdir/LICENSE" "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}

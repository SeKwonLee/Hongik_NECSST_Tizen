#!/bin/bash

skip_pkgs="bash,bzip2-libs,c-ares,cmake,coreutils,diffutils,eglibc,elfutils-libelf,elfutils-libs,elfutils,fdupes,file,findutils,gawk,gmp,libacl,libattr,libcap,libcurl,libfile,libgcc,liblua,libstdc++,make,mpc,mpfr,ncurses-libs,nodejs,nspr,nss-softokn-freebl,nss,openssl,patch,popt,rpm-libs,rpm-build,sed,sqlite,tar,xz-libs,binutils,gcc,filesystem,aul,libmm-sound,libtool,syspopup,notification,libva,libzypp-bindings,rpm"
gbs build -A armv7l --threads=2 --clean-once --include-all --exclude=${skip_pkgs}

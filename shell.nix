
with import <nixpkgs> {};
pkgs.mkShell {
  buildInputs = [ llvmPackages_10.libllvm.dev 
    libcxx
    libcxxabi
    clang_10
      llvmPackages_10.llvm.lib
      llvmPackages_10.libllvm.lib
      llvmPackages_10.libclang
      llvmPackages_10.compiler-rt
      llvmPackages_10.compiler-rt-libc
      llvmPackages_10.libcxx.dev
      llvmPackages_10.libcxxabi.dev
  ];
}

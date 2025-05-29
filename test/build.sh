clang-10 -emit-llvm -S -g *.c

for f in *.ll; do
    llvm-as-10 $f
done

mkdir -p llvm_ll
mkdir -p bitcode

mv *.ll ./llvm_ll
mv *.bc ./bitcode

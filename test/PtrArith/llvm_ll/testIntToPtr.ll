; ModuleID = 'testIntToPtr.c'
source_filename = "testIntToPtr.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@__const.main.arr = private unnamed_addr constant [5 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5], align 16
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !9 {
  %1 = alloca i32, align 4
  %2 = alloca [5 x i32], align 16
  %3 = alloca i32*, align 8
  %4 = alloca i32*, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata [5 x i32]* %2, metadata !11, metadata !DIExpression()), !dbg !15
  %5 = bitcast [5 x i32]* %2 to i8*, !dbg !15
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %5, i8* align 16 bitcast ([5 x i32]* @__const.main.arr to i8*), i64 20, i1 false), !dbg !15
  call void @llvm.dbg.declare(metadata i32** %3, metadata !16, metadata !DIExpression()), !dbg !18
  %6 = getelementptr inbounds [5 x i32], [5 x i32]* %2, i64 0, i64 0, !dbg !19
  store i32* %6, i32** %3, align 8, !dbg !18
  call void @llvm.dbg.declare(metadata i32** %4, metadata !20, metadata !DIExpression()), !dbg !21
  %7 = load i32*, i32** %3, align 8, !dbg !22
  %8 = ptrtoint i32* %7 to i32, !dbg !23
  %9 = add nsw i32 %8, 4, !dbg !24
  %10 = sext i32 %9 to i64, !dbg !23
  %11 = inttoptr i64 %10 to i32*, !dbg !23
  store i32* %11, i32** %4, align 8, !dbg !21
  %12 = load i32*, i32** %4, align 8, !dbg !25
  %13 = load i32, i32* %12, align 4, !dbg !26
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %13), !dbg !27
  ret i32 0, !dbg !28
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #2

declare dso_local i32 @printf(i8*, ...) #3

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { argmemonly nounwind willreturn }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!5, !6, !7}
!llvm.ident = !{!8}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 10.0.1-++20211003085942+ef32c611aa21-1~exp1~20211003090334.2", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, retainedTypes: !3, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "testIntToPtr.c", directory: "/home/yzh89/Documents/pdg/test/PtrArith")
!2 = !{}
!3 = !{!4}
!4 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!5 = !{i32 7, !"Dwarf Version", i32 4}
!6 = !{i32 2, !"Debug Info Version", i32 3}
!7 = !{i32 1, !"wchar_size", i32 4}
!8 = !{!"Ubuntu clang version 10.0.1-++20211003085942+ef32c611aa21-1~exp1~20211003090334.2"}
!9 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !10, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DISubroutineType(types: !3)
!11 = !DILocalVariable(name: "arr", scope: !9, file: !1, line: 4, type: !12)
!12 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 160, elements: !13)
!13 = !{!14}
!14 = !DISubrange(count: 5)
!15 = !DILocation(line: 4, column: 9, scope: !9)
!16 = !DILocalVariable(name: "ptr", scope: !9, file: !1, line: 5, type: !17)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!18 = !DILocation(line: 5, column: 10, scope: !9)
!19 = !DILocation(line: 5, column: 16, scope: !9)
!20 = !DILocalVariable(name: "k", scope: !9, file: !1, line: 6, type: !17)
!21 = !DILocation(line: 6, column: 9, scope: !9)
!22 = !DILocation(line: 6, column: 18, scope: !9)
!23 = !DILocation(line: 6, column: 13, scope: !9)
!24 = !DILocation(line: 6, column: 22, scope: !9)
!25 = !DILocation(line: 7, column: 21, scope: !9)
!26 = !DILocation(line: 7, column: 20, scope: !9)
!27 = !DILocation(line: 7, column: 5, scope: !9)
!28 = !DILocation(line: 8, column: 5, scope: !9)

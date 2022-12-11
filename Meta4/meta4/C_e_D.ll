@global.var.a = common global i32 0, align 4
@global.var.b = common global i32 0, align 4
@global.var.c = common global i32 0, align 4
@global.var.d = common global i32 0, align 4
declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	call void @function.declaration.v.main.s.(i32 %argc, i8** %argv)
	ret i32 0
}

define void @function.declaration.v.main.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%1 = load i32, i32* @global.var.a, align 4
	%2 = add i32 0, 2
	store i32 %2, i32* @global.var.a, align 4
	%3 = load i32, i32* @global.var.a, align 4
	%4 = load i32, i32* @global.var.a, align 4
	%5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.1, i32 0, i32 0), i32 %4)
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	%i = alloca i32, align 4
	%a = alloca i32, align 4
	%i1 = alloca i32, align 4
	%i2 = alloca i32, align 4
	%i3 = alloca i32, align 4
	%d = alloca double, align 8
	%7 = load double, double* %d, align 8
	%8 = load i32, i32* %a, align 4
	%9 = add i32 0, 0
	%10 = add i32 0, 3
	%11 = add i32 %9, %10
	store i32 %11, i32* %a, align 4
	%12 = load i32, i32* %a, align 4
	%convertion.1 = sitofp i32 %12 to double
	store double %convertion.1, double* %d, align 8
	%13 = load double, double* %d, align 8
	%14 = load i32, i32* %a, align 4
	%15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.3, i32 0, i32 0), i32 %14)
	%16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.4, i32 0, i32 0))
	%17 = load double, double* %d, align 8
	%18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.5, i32 0, i32 0), double %17)
	%19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.6, i32 0, i32 0))
	%20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.global.strlit.7, i32 0, i32 0))
	%21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.8, i32 0, i32 0))
	%22 = load i32, i32* %a, align 4
	%23 = load i32, i32* %a, align 4
	%24 = add i32 0, 1
	%25 = add i32 %23, %24
	store i32 %25, i32* %a, align 4
	%26 = load i32, i32* %a, align 4
	%27 = add i32 0, 0
	%28 = icmp sgt i32 %26, %27
	br label %label.entry1
label.entry1:        ;it's an or
	%29 = icmp eq i1 %28, 0
	br i1 %29, label %label.transition1, label %label.end1
label.transition1:       ;transition of an or
	%30 = load i32, i32* %a, align 4
	%31 = load i32, i32* %a, align 4
	%32 = add i32 0, 3
	%33 = add i32 %31, %32
	store i32 %33, i32* %a, align 4
	%34 = load i32, i32* %a, align 4
	%35 = add i32 0, 0
	%36 = icmp sgt i32 %34, %35
	%37 = icmp eq i1 %36, 1
	br label %label.end1
label.end1:      ; it's the end of an or
	%38 = phi i1 [ 1, %label.entry1 ], [ %37, %label.transition1 ]
	%compare.1 = icmp eq i1 %38, 1
	br i1 %compare.1, label %compare.if.1, label %compare.else.1
	compare.if.1:
		%39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.9, i32 0, i32 0))
		br label %compare.end.1
	compare.else.1:
		%40 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.10, i32 0, i32 0))
		br label %compare.end.1
	compare.end.1:
	%41 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.11, i32 0, i32 0))
	%42 = load i32, i32* %a, align 4
	%43 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.12, i32 0, i32 0), i32 %42)
	%44 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.13, i32 0, i32 0))
	%45 = load i32, i32* %a, align 4
	%46 = load i32, i32* %a, align 4
	%47 = add i32 0, 1
	%48 = add i32 %46, %47
	store i32 %48, i32* %a, align 4
	%49 = load i32, i32* %a, align 4
	%50 = add i32 0, 0
	%51 = icmp slt i32 %49, %50
	br label %label.entry2
label.entry2:        ;it's an and
	%52 = icmp eq i1 %51, 1
	br i1 %52, label %label.transition2, label %label.end2
label.transition2:       ;transition of an and
	%53 = load i32, i32* %a, align 4
	%54 = load i32, i32* %a, align 4
	%55 = add i32 0, 3
	%56 = add i32 %54, %55
	store i32 %56, i32* %a, align 4
	%57 = load i32, i32* %a, align 4
	%58 = add i32 0, 0
	%59 = icmp slt i32 %57, %58
	%60 = icmp eq i1 %59, 1
	br label %label.end2
label.end2:      ; it's the end of an and
	%61 = phi i1 [ 0, %label.entry2 ], [ %60, %label.transition2 ]
	%compare.2 = icmp eq i1 %61, 1
	br i1 %compare.2, label %compare.if.2, label %compare.else.2
	compare.if.2:
		%62 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.14, i32 0, i32 0))
		br label %compare.end.2
	compare.else.2:
		%63 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.15, i32 0, i32 0))
		br label %compare.end.2
	compare.end.2:
	%64 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.16, i32 0, i32 0))
	%65 = load i32, i32* %a, align 4
	%66 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.17, i32 0, i32 0), i32 %65)
	%67 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.18, i32 0, i32 0))
	%68 = load double, double* %d, align 8
	%69 = fadd double 0.000000e+00, 1.2299999999999999e-08
	store double %69, double* %d, align 8
	%70 = load double, double* %d, align 8
	%71 = load double, double* %d, align 8
	%72 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.19, i32 0, i32 0), double %71)
	%73 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.20, i32 0, i32 0))
	%74 = load double, double* %d, align 8
	%75 = fadd double 0.000000e+00, 0.0000000000000000e+00
	store double %75, double* %d, align 8
	%76 = load double, double* %d, align 8
	%77 = load double, double* %d, align 8
	%78 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.21, i32 0, i32 0), double %77)
	%79 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.22, i32 0, i32 0))
	%80 = load double, double* %d, align 8
	%81 = fadd double 0.000000e+00, 1.0000000000000000e+01
	store double %81, double* %d, align 8
	%82 = load double, double* %d, align 8
	%83 = load double, double* %d, align 8
	%84 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.23, i32 0, i32 0), double %83)
	%85 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.24, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.5 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.7 = private unnamed_addr constant [24 x i8] c"Teste\09de \0Cstring\5C\22\0D%%%%\00", align 1
@.global.strlit.8 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.9 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.10 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.11 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.12 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.13 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.14 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.15 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.16 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.17 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.18 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.19 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.20 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.21 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.22 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.23 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.24 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

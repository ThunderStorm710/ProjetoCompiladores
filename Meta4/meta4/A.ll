@global.var.global_var = common global i32 0, align 4
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
	%a = alloca i32, align 4
	%b = alloca i1
	%c = alloca double, align 8
	%1 = load i32, i32* %a, align 4
	%2 = add i32 0, 1
	store i32 %2, i32* %a, align 4
	%3 = load i32, i32* %a, align 4
	%4 = load i32, i32* %a, align 4
	%5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.1, i32 0, i32 0), i32 %4)
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	%7 = load i32, i32* %a, align 4
	%8 = add i32 0, 1
	store i32 %8, i32* %a, align 4
	%9 = load i32, i32* %a, align 4
	%10 = load i32, i32* %a, align 4
	%11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.3, i32 0, i32 0), i32 %10)
	%12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.4, i32 0, i32 0))
	%13 = load i32, i32* %a, align 4
	%14 = add i32 0, 1
	%15 = sub nsw i32 0, %14
	store i32 %15, i32* %a, align 4
	%16 = load i32, i32* %a, align 4
	%17 = load i32, i32* %a, align 4
	%18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.5, i32 0, i32 0), i32 %17)
	%19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.6, i32 0, i32 0))
	%20 = load i1, i1* %b
	%21 = add i1 0, 1
	store i1 %21, i1* %b
	%22 = load i1, i1* %b
	%23 = load i1, i1* %b
	%compare.1 = icmp eq i1 %23, 1
	br i1 %compare.1, label %compare.if.1, label %compare.else.1
	compare.if.1:
		%24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.7, i32 0, i32 0))
		br label %compare.end.1
	compare.else.1:
		%25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.8, i32 0, i32 0))
		br label %compare.end.1
	compare.end.1:
	%26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.9, i32 0, i32 0))
	%27 = load i1, i1* %b
	%28 = add i1 0, 0
	store i1 %28, i1* %b
	%29 = load i1, i1* %b
	%30 = load i1, i1* %b
	%compare.2 = icmp eq i1 %30, 1
	br i1 %compare.2, label %compare.if.2, label %compare.else.2
	compare.if.2:
		%31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.10, i32 0, i32 0))
		br label %compare.end.2
	compare.else.2:
		%32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.11, i32 0, i32 0))
		br label %compare.end.2
	compare.end.2:
	%33 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.12, i32 0, i32 0))
	%34 = load double, double* %c, align 8
	%35 = fadd double 0.000000e+00, 2.0000000000000000e+00
	store double %35, double* %c, align 8
	%36 = load double, double* %c, align 8
	%37 = load double, double* %c, align 8
	%38 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.13, i32 0, i32 0), double %37)
	%39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.14, i32 0, i32 0))
	%40 = load double, double* %c, align 8
	%41 = fadd double 0.000000e+00, 2.2000000000000002e+00
	store double %41, double* %c, align 8
	%42 = load double, double* %c, align 8
	%43 = load double, double* %c, align 8
	%44 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.15, i32 0, i32 0), double %43)
	%45 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.16, i32 0, i32 0))
	%46 = load double, double* %c, align 8
	%47 = add i32 0, 2
	%convertion.1 = sitofp i32 %47 to double
	store double %convertion.1, double* %c, align 8
	%48 = load double, double* %c, align 8
	%49 = load double, double* %c, align 8
	%50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.17, i32 0, i32 0), double %49)
	%51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.18, i32 0, i32 0))
	%52 = load i32, i32* %a, align 4
	%53 = add i32 0, 1
	store i32 %53, i32* %a, align 4
	%54 = load i32, i32* %a, align 4
	%55 = load double, double* %c, align 8
	%56 = load i32, i32* %a, align 4
	%convertion.2 = sitofp i32 %56 to double
	store double %convertion.2, double* %c, align 8
	%57 = load double, double* %c, align 8
	%58 = load double, double* %c, align 8
	%59 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.19, i32 0, i32 0), double %58)
	%60 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.20, i32 0, i32 0))
	%61 = load double, double* %c, align 8
	%62 = fadd double 0.000000e+00, 2.2000000000000002e+00
	store double %62, double* %c, align 8
	%63 = load double, double* %c, align 8
	%64 = load double, double* %c, align 8
	%65 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.21, i32 0, i32 0), double %64)
	%66 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.22, i32 0, i32 0))
	%67 = load double, double* %c, align 8
	%68 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%69 = fsub double -0.000000e+00, %68
	store double %69, double* %c, align 8
	%70 = load double, double* %c, align 8
	%71 = load double, double* %c, align 8
	%72 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.23, i32 0, i32 0), double %71)
	%73 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.24, i32 0, i32 0))
	%74 = load double, double* %c, align 8
	%75 = load i32, i32* %a, align 4
	%convertion.3 = sitofp i32 %75 to double
	store double %convertion.3, double* %c, align 8
	%76 = load double, double* %c, align 8
	%77 = load double, double* %c, align 8
	%78 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.25, i32 0, i32 0), double %77)
	%79 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.26, i32 0, i32 0))
	%80 = load double, double* %c, align 8
	%81 = load i32, i32* %a, align 4
	%82 = sub nsw i32 0, %81
	%convertion.4 = sitofp i32 %82 to double
	store double %convertion.4, double* %c, align 8
	%83 = load double, double* %c, align 8
	%84 = load double, double* %c, align 8
	%85 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.27, i32 0, i32 0), double %84)
	%86 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.28, i32 0, i32 0))
	%87 = load i32, i32* @global.var.global_var, align 4
	%88 = add i32 0, 10
	store i32 %88, i32* @global.var.global_var, align 4
	%89 = load i32, i32* @global.var.global_var, align 4
	%90 = load i32, i32* @global.var.global_var, align 4
	%91 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.29, i32 0, i32 0), i32 %90)
	%92 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.30, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.5 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.7 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.8 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.9 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.10 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.11 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.12 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.13 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.14 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.15 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.16 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.17 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.18 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.19 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.20 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.21 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.22 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.23 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.24 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.25 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.26 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.27 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.28 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.29 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.30 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

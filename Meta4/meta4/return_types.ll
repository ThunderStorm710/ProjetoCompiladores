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
	%d = alloca double, align 8
	%1 = load double, double* %d, align 8
	%2 = call double @function.declaration.d.fun_double.()
	store double %2, double* %d, align 8
	%3 = load double, double* %d, align 8
	%4 = load double, double* %d, align 8
	%5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.1, i32 0, i32 0), double %4)
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	%7 = load double, double* %d, align 8
	%8 = call i32 @function.declaration.i.fun_int.()
	%convertion.1 = sitofp i32 %8 to double
	store double %convertion.1, double* %d, align 8
	%9 = load double, double* %d, align 8
	%10 = load double, double* %d, align 8
	%11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.3, i32 0, i32 0), double %10)
	%12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.4, i32 0, i32 0))
	%13 = load double, double* %d, align 8
	%14 = call double @function.declaration.d.fun_double_from_int.()
	store double %14, double* %d, align 8
	%15 = load double, double* %d, align 8
	%16 = load double, double* %d, align 8
	%17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.5, i32 0, i32 0), double %16)
	%18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.6, i32 0, i32 0))
	%19 = load double, double* %d, align 8
	%20 = call double @function.declaration.d.fun_double_from_int_fun.()
	store double %20, double* %d, align 8
	%21 = load double, double* %d, align 8
	%22 = load double, double* %d, align 8
	%23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.7, i32 0, i32 0), double %22)
	%24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.8, i32 0, i32 0))
	%25 = load double, double* %d, align 8
	%26 = call double @function.declaration.d.fun_double_from_int_var.()
	store double %26, double* %d, align 8
	%27 = load double, double* %d, align 8
	%28 = load double, double* %d, align 8
	%29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.9, i32 0, i32 0), double %28)
	%30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.10, i32 0, i32 0))
	%31 = load double, double* %d, align 8
	%32 = call double @function.declaration.d.fun_double_from_args.s.(i32 %argc, i8** %argv)
	store double %32, double* %d, align 8
	%33 = load double, double* %d, align 8
	%34 = load double, double* %d, align 8
	%35 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.11, i32 0, i32 0), double %34)
	%36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.12, i32 0, i32 0))
	%37 = load double, double* %d, align 8
	%38 = call double @function.declaration.d.fun_double_from_unary_plus.s.(i32 %argc, i8** %argv)
	store double %38, double* %d, align 8
	%39 = load double, double* %d, align 8
	%40 = load double, double* %d, align 8
	%41 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.13, i32 0, i32 0), double %40)
	%42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.14, i32 0, i32 0))
	%43 = fadd double 0.000000e+00, 1.3000000000000000e+00
	%44 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.15, i32 0, i32 0), double %43)
	%45 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.16, i32 0, i32 0))
	ret void
}
define double @function.declaration.d.fun_double.() {
	%1 = fadd double 0.000000e+00, 1.1000000000000001e+00
	ret double %1
	ret double 0.000000e+00
}
define i32 @function.declaration.i.fun_int.() {
	%1 = add i32 0, 1
	ret i32 %1
	ret i32 0
}
define double @function.declaration.d.fun_double_from_int.() {
	%1 = add i32 0, 2
	%2 = sitofp i32 %1 to double
	ret double %2
	ret double 0.000000e+00
}
define double @function.declaration.d.fun_double_from_int_fun.() {
	%1 = call i32 @function.declaration.i.fun_int.()
	%2 = sitofp i32 %1 to double
	ret double %2
	ret double 0.000000e+00
}
define double @function.declaration.d.fun_double_from_int_var.() {
	%d = alloca double, align 8
	%1 = load double, double* %d, align 8
	%2 = add i32 0, 0
	%convertion.1 = sitofp i32 %2 to double
	store double %convertion.1, double* %d, align 8
	%3 = load double, double* %d, align 8
	%4 = load double, double* %d, align 8
	%5 = call i32 @function.declaration.i.fun_int.()
	%6 = sitofp i32 %5 to double
	%7 = fadd double %4, %6
	%8 = call double @function.declaration.d.fun_double.()
	%9 = fadd double %7, %8
	ret double %9
	ret double 0.000000e+00
}
define double @function.declaration.d.fun_double_from_args.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%1 = load i32, i32* %argc_aux, align 4
	%2 = sub i32 %1, 1
	%3 = sitofp i32 %2 to double
	ret double %3
	ret double 0.000000e+00
}
define double @function.declaration.d.fun_double_from_unary_plus.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%1 = add i32 0, 1
	%2 = sitofp i32 %1 to double
	ret double %2
	ret double 0.000000e+00
}

@.global.strlit.1 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.3 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.5 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.7 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.8 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.9 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.10 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.11 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.12 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.13 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.14 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.15 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.16 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

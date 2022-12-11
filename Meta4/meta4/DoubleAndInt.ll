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
	%i = alloca i32, align 4
	%1 = load i32, i32* %i, align 4
	%2 = add i32 0, 3
	store i32 %2, i32* %i, align 4
	%3 = load i32, i32* %i, align 4
	%j = alloca double, align 8
	%4 = load double, double* %j, align 8
	%5 = add i32 0, 4
	%convertion.1 = sitofp i32 %5 to double
	store double %convertion.1, double* %j, align 8
	%6 = load double, double* %j, align 8
	%7 = load double, double* %j, align 8
	%8 = load i32, i32* %i, align 4
	%9 = load double, double* %j, align 8
	%10 = sitofp i32 %8 to double
	%11 = fadd double %10, %9
	store double %11, double* %j, align 8
	%12 = load double, double* %j, align 8
	%13 = load double, double* %j, align 8
	%14 = load i32, i32* %i, align 4
	%15 = load double, double* %j, align 8
	%16 = sitofp i32 %14 to double
	%17 = fdiv double %16, %15
	store double %17, double* %j, align 8
	%18 = load double, double* %j, align 8
	%19 = load double, double* %j, align 8
	%20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.1, i32 0, i32 0), double %19)
	%21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

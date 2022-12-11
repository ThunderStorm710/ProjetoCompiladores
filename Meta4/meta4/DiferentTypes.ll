declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	call void @function.declaration.v.main.s.(i32 %argc, i8** %argv)
	ret i32 0
}

define i1 @function.declaration.b.bool.() {
	%i = alloca i1
	%1 = load i1, i1* %i
	%2 = add i1 0, 1
	store i1 %2, i1* %i
	%3 = load i1, i1* %i
	%4 = load i1, i1* %i
	%compare.1 = icmp eq i1 %4, 1
	br i1 %compare.1, label %compare.if.1, label %compare.else.1
	compare.if.1:
		%5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.1, i32 0, i32 0))
		br label %compare.end.1
	compare.else.1:
		%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.2, i32 0, i32 0))
		br label %compare.end.1
	compare.end.1:
	%7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.3, i32 0, i32 0))
	%8 = load i1, i1* %i
	ret i1 %8
	ret i1 1
}
define i32 @function.declaration.i.integer.() {
	%i = alloca i32, align 4
	%1 = load i32, i32* %i, align 4
	%2 = add i32 0, 1
	store i32 %2, i32* %i, align 4
	%3 = load i32, i32* %i, align 4
	%4 = load i32, i32* %i, align 4
	%5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.4, i32 0, i32 0), i32 %4)
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.5, i32 0, i32 0))
	%7 = load i32, i32* %i, align 4
	ret i32 %7
	ret i32 0
}
define double @function.declaration.d.real.() {
	%i = alloca double, align 8
	%1 = load double, double* %i, align 8
	%2 = fadd double 0.000000e+00, 1.0000000000000000e+00
	store double %2, double* %i, align 8
	%3 = load double, double* %i, align 8
	%4 = load double, double* %i, align 8
	%5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.6, i32 0, i32 0), double %4)
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.7, i32 0, i32 0))
	%7 = load double, double* %i, align 8
	ret double %7
	ret double 0.000000e+00
}
define void @function.declaration.v.main.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%1 = call i1 @function.declaration.b.bool.()
	%2 = call i32 @function.declaration.i.integer.()
	%3 = call double @function.declaration.d.real.()
	%4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.8, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.2 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.6 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.7 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.8 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

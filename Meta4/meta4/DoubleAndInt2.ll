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
	%7 = load i32, i32* %i, align 4
	%8 = add i32 0, 1
	%9 = add i32 %7, %8
	%10 = load double, double* %j, align 8
	%11 = sitofp i32 %9 to double
	%12 = fcmp oeq double %11, %10
	br label %label.entry.if1
label.entry.if1:       ;it's if 
	%13 = icmp eq i1 %12, 1
	br i1 %13, label %label.then1, label %label.else1
label.then1:       ;it's if 
	%14 = load double, double* %j, align 8
	%15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.1, i32 0, i32 0), double %14)
br label %label.finished.if1
label.else1:       ;it's else 
br label %label.finished.if1
label.finished.if1:
	%16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

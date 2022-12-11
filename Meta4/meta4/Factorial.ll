declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	call void @function.declaration.v.main.s.(i32 %argc, i8** %argv)
	ret i32 0
}

define i32 @function.declaration.i.factorial.i.(i32 %n_aux) {
	%n = alloca i32, align 4
	store i32 %n_aux, i32* %n, align 4
	%1 = load i32, i32* %n, align 4
	%2 = add i32 0, 0
	%3 = icmp eq i32 %1, %2
	br label %label.entry.if1
label.entry.if1:       ;it's if 
	%4 = icmp eq i1 %3, 1
	br i1 %4, label %label.then1, label %label.else1
label.then1:       ;it's if 
	%5 = add i32 0, 1
	ret i32 %5
br label %label.finished.if1
label.else1:       ;it's else 
br label %label.finished.if1
label.finished.if1:
	%7 = load i32, i32* %n, align 4
	%8 = load i32, i32* %n, align 4
	%9 = add i32 0, 1
	%10 = sub i32 %8, %9
	%11 = call i32 @function.declaration.i.factorial.i.(i32 %10)
	%12 = mul i32 %7, %11
	ret i32 %12
	ret i32 0
}
define void @function.declaration.v.main.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%argument = alloca i32, align 4
	%1 = load i32, i32* %argument, align 4
	%2 = add i32 0, 7
	store i32 %2, i32* %argument, align 4
	%3 = load i32, i32* %argument, align 4
	%4 = load i32, i32* %argument, align 4
	%5 = call i32 @function.declaration.i.factorial.i.(i32 %4)
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.1, i32 0, i32 0), i32 %5)
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1

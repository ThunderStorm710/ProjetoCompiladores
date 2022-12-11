@global.var.overload = common global i32 0, align 4
declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	call void @function.declaration.v.main.s.(i32 %argc, i8** %argv)
	ret i32 0
}

define void @function.declaration.v.overload.i.(i32 %n_aux) {
	%n = alloca i32, align 4
	store i32 %n_aux, i32* %n, align 4
	%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.global.strlit.1, i32 0, i32 0))
	ret void
}
define void @function.declaration.v.overload.() {
	%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.global.strlit.2, i32 0, i32 0))
	ret void
}
define void @function.declaration.v.main.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%1 = load i32, i32* %argc_aux, align 4
	%2 = sub i32 %1, 1
	%3 = add i32 0, 0
	%4 = icmp sgt i32 %2, %3
	br label %label.entry.if1
label.entry.if1:       ;it's if 
	%5 = icmp eq i1 %4, 1
	br i1 %5, label %label.then1, label %label.else1
label.then1:       ;it's if 
	%6 = add i32 0, 0
	%7 = add i32 %6, 1
	%8 = load i8**, i8*** %argv_aux, align 8
	%9 = getelementptr inbounds i8*, i8** %8, i32 %7
	%10 = load i8*, i8** %9, align 8
	%11 = call i32 @atoi(i8* %10)
	call void @function.declaration.v.overload.i.(i32 %11)
br label %label.finished.if1
label.else1:       ;it's else 
	call void @function.declaration.v.overload.()
br label %label.finished.if1
label.finished.if1:
	%12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.3, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [19 x i8] c"I have a parameter\00", align 1
@.global.strlit.2 = private unnamed_addr constant [25 x i8] c"I don't have a parameter\00", align 1
@.global.strlit.3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	ret i32 0
}

define i32 @function.declaration.i.a.i.(i32 %input_aux) {
	%input = alloca i32, align 4
	store i32 %input_aux, i32* %input, align 4
	%1 = load i32, i32* %input, align 4
	ret i32 %1
	ret i32 0
}
define i32 @function.declaration.i.b.i.(i32 %input_aux) {
	%input = alloca i32, align 4
	store i32 %input_aux, i32* %input, align 4
	%1 = load i32, i32* %input, align 4
	ret i32 %1
	ret i32 0
}


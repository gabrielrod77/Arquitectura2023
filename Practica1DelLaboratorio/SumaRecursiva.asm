.data

prompt1:  .asciiz "introduce el número n\n"
prompt2:  .asciiz "introduce el valor del acumulador\n"
resultado: .asciiz "el resultado es:"

.text
########
# Programa por Gabriel Rodríguez 
# C.I.30172571
# 27/11/23
# Este programa realiza una suma recursiva
########
	addi $v0, $zero, 4  
	la $a0, prompt1
	syscall			# muestra en pantalla el mensaje reservado en prompt1

	addi $v0, $zero, 5
	syscall			#pide al usuario ingresar el número que se le va aplicar la suma recursiva(n)
	
	add $t0, $v0, $zero
	
	addi $v0, $zero, 4
	la $a0, prompt2
	syscall			# muestra en pantalla el mensaje reservado en prompt2

	addi $v0, $zero, 5
	syscall			#pide al usuario ingresar el valor del acumulador
	add $a1, $v0, $zero
	add $a0, $t0, $zero

sum:	slti $t0 ,$a0, 1
	bne $t0, $zero, sum_exit
	add $a1, $a1, $a0
	addi $a0, $a0, -1
	j sum
sum_exit:
	# add $v0, $a1, $zero
	la $a0, resultado
	addi $v0, $zero, 4
	syscall
	
	add $a0, $a1, $zero
	addi $v0, $zero, 1
	syscall

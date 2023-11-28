.data
senc: .word 0 : 100 	#ingrese el tamaño máximo del vector
#tamano: .word 7		#ingrese el tamaño del vector
espacio: .asciiz " "
prompt1: .asciiz "Introduzca el tamaño del vector(entre 1 y 100)\n"
prompt2: .asciiz "Introduzca los elementos del vector\n"
.text
########
# Programa por Gabriel Rodríguez 
# C.I.30172571
# 27/11/23
# Este programa ordena un vector de forma ascendente usando el método burbuja bidireccional(cocktailSort)
########
		la $s2, senc
		#la $a1, tamano
		#lw $a1, 0($a1)
		
		la $a0, prompt1
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		add $a1, $zero, $v0
		addi $t3, $zero, 1	# i = 1
		la $a0, prompt2
		li $v0, 4
		syscall
		
llenar:		li $v0, 5
		syscall
		sw $v0,0($s2)
		slt $t0, $t3, $a1
		addi $s2, $s2, 4
		addi $t3, $t3, 1
		bne $t0, $zero, llenar
		
		addi $s1, $a1, -1 #$a1 es la longitud del vector
		move $s0, $zero
		move $t3, $zero
		la $a0, senc
		
mientras:	sub $t4, $s1, $s0
		#addi $t4, $t4, -1
		beq $t4, $zero, fin
		beq $t3, $s1, sortDer
		
sortIzq:	
		lw $t0, 0($a0)
		lw $t1, 4($a0)
		slt $t2, $t1, $t0
		bne $t2, $zero, cambiarI
		
contIzq:	addi $a0, $a0, 4
		addi $t3, $t3, 1
		beq $t3, $s1, FinIzq
		j sortIzq

sortDer:	lw $t0, 0($a0)
		lw $t1, -4($a0)
		slt $t2, $t0, $t1
		bne $t2, $zero, cambiarD
		
contDer:		
		addi $a0, $a0, -4 # k = k-1
		addi $t3, $t3, -1	# i = i-1
		beq $t3, $s0, FinDer
		j sortDer


cambiarI:	sw $t0, 4($a0)
		sw $t1, 0($a0)
		j contIzq
		
cambiarD:	sw $t0, -4($a0)
		sw $t1, 0($a0)
		j contDer
		
FinIzq:		addi $s1, $s1, -1
		addi $t3, $t3, -1	#der = der - 1
		addi $a0, $a0, -4	
		j mientras

FinDer:		addi $s0, $s0, 1
		addi $t3, $t3, 1	#izq = izq + 1
		addi $a0, $a0, 4	
		j mientras
		
fin:		la $s2, senc
		addi $t3, $zero, 1
imprimir:	
		lw $a0,0($s2)
		li $v0, 1
		syscall
		la $a0, espacio
		li $v0, 4
		syscall
		slt $t0, $t3, $a1
		addi $s2, $s2, 4
		addi $t3, $t3, 1
		bne $t0, $zero, imprimir

		li, $v0,10
		syscall

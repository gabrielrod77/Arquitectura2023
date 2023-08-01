.data
prompt1: .asciiz "Introduce el indice de la sequencia\n"
prompt2: .asciiz "El valor de Fibonacci es:\n"

.text

li $v0, 4
la $a0, prompt1
syscall


li $v0, 5
syscall


move $a0, $v0
jal fibonacci
move $a1, $v0


li $v0, 4
la $a0, prompt2
syscall


li $v0, 1
move $a0, $a1
syscall


li $v0, 10
syscall



## Funcion fibonacci (int n)
fibonacci:
# Prologo
addi $sp, $sp, -12
sw $ra, 8($sp)
sw $s0, 4($sp)
sw $s1, 0($sp)
move $s0, $a0
li $v0, 1 
ble $s0, 0x2, fibonacciSalida 
addi $a0, $s0, -1 
jal fibonacci
move $s1, $v0 
addi $a0, $s0, -2 
jal fibonacci
add $v0, $s1, $v0 
fibonacciSalida:

lw $ra, 8($sp)
lw $s0, 4($sp)
lw $s1, 0($sp)
addi $sp, $sp, 12
jr $ra

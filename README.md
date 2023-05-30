# VMM_hypervisorModule

Built a hypervisor module, which parses the MIPS assembly instructions using cpp. This link consists of all the available instructions https://www.dsi.unive.it/~gasparetto/materials/MIPS_Instruction_Set.pdf

The instructions will be sent to the parser in this format:

li $1,6
li $2,9
li $3,12
add $4,$1,$2
sub $5,$2,$1
addi $6,$3,15
SNAPSHOT snapshot_vm1
mul $7,$4,$5
and $8,$2,$3
or $9,$1,$4
xor $10,$6,$8
or $11,$4,100
sll $12,$7,10
srl $13,$8,10
DUMP_PROCESSOR_STATE

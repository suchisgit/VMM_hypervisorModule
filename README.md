# VMM_hypervisorModule

Built a hypervisor module, which parses the MIPS assembly instructions using cpp. This link consists of all the available instructions https://www.dsi.unive.it/~gasparetto/materials/MIPS_Instruction_Set.pdf

The instructions will be sent to the parser in this format:

li $1,6 <br>
li $2,9 <br>
li $3,12 <br>
add $4,$1,$2 <br>
sub $5,$2,$1 <br>
addi $6,$3,15 <br>
SNAPSHOT snapshot_vm1 <br>
mul $7,$4,$5 <br>
and $8,$2,$3 <br>
or $9,$1,$4 <br>
xor $10,$6,$8 <br>
or $11,$4,100 <br>
sll $12,$7,10 <br>
srl $13,$8,10 <br>
DUMP_PROCESSOR_STATE  <br>

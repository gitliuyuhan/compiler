ASSUME CS:codesg,DS:datasg
datasg segment
    a DB '?'
    b DB '?'
    tmpB DB '?'
    tmpC DB '?'
    tmpD DB '?'
    tmpE DB 'a=$'
    tmpF DB ' b=$'
datasg ends
codesg segment
  start:
    mov AX,datasg
    mov DS,AX
    mov BL,4
    mov a,BL
    mov BL,2
    mov b,BL
    mov AL,a
    CMP AL,b
    JG stepB
    JMP stepC
  stepB:
    mov BL,a
    add BL,1
    mov tmpB,BL
    mov BL,tmpB
    mov a,BL
    JMP stepC
  stepC:
    mov AL,b
    CMP AL,1
    JL stepD
    mov BL,b
    add BL,1
    mov tmpC,BL
    mov BL,tmpC
    mov b,BL
    JMP stepE
  stepD:
    mov BL,b
    sub BL,1
    mov tmpD,BL
    mov BL,tmpD
    mov b,BL
    JMP stepE
  stepE:
    LEA DX,tmpE
    mov AH,09
    int 21H
    mov AL,a
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepG
  stepF:
    mov DL,AL
    mov AH,2
    int 21H
  stepG:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpF
    mov AH,09
    int 21H
    mov AL,b
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepI
  stepH:
    mov DL,AL
    mov AH,2
    int 21H
  stepI:
    mov DL,BH
    mov AH,2
    int 21H
    mov ax,4C00H
    int 21H
codesg ends
  end start

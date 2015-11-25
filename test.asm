ASSUME CS:codesg,DS:datasg
datasg segment
    x DB '?'
    y DB 1
    z DB '?'
    tmpB DB '?'
    tmpC DB '?'
    tmpD DB 'x=$'
    tmpE DB '  y=$'
    tmpF DB '  z=$'
datasg ends
codesg segment
  start:
    mov AX,datasg
    mov DS,AX
    mov BL,1
    mov y,BL
    mov BL,y
    add BL,20
    mov tmpB,BL
    mov BL,tmpB
    mov x,BL
    mov BL,x
    add BL,y
    mov tmpC,BL
    mov BL,tmpC
    mov z,BL
    LEA DX,tmpD
    mov AH,09
    int 21H
    mov AL,x
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepC
  stepB:
    mov DL,AL
    mov AH,2
    int 21H
  stepC:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpE
    mov AH,09
    int 21H
    mov AL,y
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepE
  stepD:
    mov DL,AL
    mov AH,2
    int 21H
  stepE:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpF
    mov AH,09
    int 21H
    mov AL,z
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
    mov ax,4C00H
    int 21H
codesg ends
  end start

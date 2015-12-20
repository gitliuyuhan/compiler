ASSUME CS:codesg,DS:datasg
datasg segment
    x DB '?'
    y DB '?'
    z DB '?'
    tmpB DB '?'
    tmpC DB 'z=$'
datasg ends
codesg segment
  start:
    mov AX,datasg
    mov DS,AX
    mov BL,5
    mov x,BL
    mov BL,4
    mov y,BL
    mov BL,x
    add BL,y
    mov tmpB,BL
    mov BL,tmpB
    mov z,BL
    LEA DX,tmpC
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
    JE stepC
  stepB:
    mov DL,AL
    mov AH,2
    int 21H
  stepC:
    mov DL,BH
    mov AH,2
    int 21H
    mov ax,4C00H
    int 21H
codesg ends
  end start

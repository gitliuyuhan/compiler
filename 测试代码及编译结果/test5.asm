ASSUME CS:codesg,DS:datasg
datasg segment
    x DB '?'
    tmpB DB '?'
datasg ends
codesg segment
  start:
    mov AX,datasg
    mov DS,AX
    mov BL,x
    add BL,1
    mov tmpB,BL
    mov BL,tmpB
    mov x,BL
    mov ax,4C00H
    int 21H
codesg ends
  end start

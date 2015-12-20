ASSUME CS:codesg,DS:datasg
datasg segment
    a DB '?'
    b DB '?'
    c DB '?'
    d DB '?'
    tmpB DB '?'
    tmpC DB '?'
    tmpD DB '?'
    tmpE DB 'a=$'
    tmpF DB '  b=$'
    tmpG DB '  c=$'
    tmpH DB '  d=$'
    tmpI DB '?'
    tmpJ DB '  d=$'
datasg ends
codesg segment
  start:
    mov AX,datasg
    mov DS,AX
    mov BL,0
    mov a,BL
    mov BL,a
    add BL,1
    mov tmpB,BL
    mov BL,tmpB
    mov b,BL
    mov BL,10
    sub BL,b
    mov tmpC,BL
    mov BL,tmpC
    mov c,BL
    mov AL,b
    mov BH,c
    mul BH
    mov BL,1
    div BL
    mov tmpD,AL
    mov BL,tmpD
    mov d,BL
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
    JE stepC
  stepB:
    mov DL,AL
    mov AH,2
    int 21H
  stepC:
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
    JE stepE
  stepD:
    mov DL,AL
    mov AH,2
    int 21H
  stepE:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpG
    mov AH,09
    int 21H
    mov AL,c
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
    LEA DX,tmpH
    mov AH,09
    int 21H
    mov AL,d
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
    mov AL,c
    CBW
    mov BL,3
    div BL
    mov tmpI,AL
    mov BL,tmpI
    mov d,BL
    LEA DX,tmpJ
    mov AH,09
    int 21H
    mov AL,d
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepK
  stepJ:
    mov DL,AL
    mov AH,2
    int 21H
  stepK:
    mov DL,BH
    mov AH,2
    int 21H
    mov ax,4C00H
    int 21H
codesg ends
  end start

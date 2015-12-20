ASSUME CS:codesg,DS:datasg
datasg segment
    x1 DB '?'
    y1 DB 2
    x2 DB '?'
    y2 DB '?'
    x3 DB '?'
    y3 DB '?'
    x4 DB 4
    y4 DB 8
    ch DB '9'
    tmpB DB 'ch_char $'
    tmpC DB '   ch_int $'
    tmpD DB '?'
    tmpE DB '?'
    tmpF DB '?'
    tmpG DB '?'
    tmpH DB '?'
    tmpI DB '  x1=$'
    tmpJ DB ' y1=$'
    tmpK DB ' x2=$'
    tmpL DB ' y2=$'
    tmpM DB ' x3=$'
    tmpN DB ' y3=$'
    tmpO DB ' x4=$'
    tmpP DB ' y4=$'
    tmpQ DB '?'
    tmpR DB '?'
    tmpS DB '?'
    tmpT DB '?'
    tmpU DB '?'
    tmpV DB '?'
    tmpW DB '?'
    tmpX DB '?'
    tmpY DB '   result = $'
datasg ends
codesg segment
  start:
    mov AX,datasg
    mov DS,AX
    mov BL,2
    mov y1,BL
    mov BL,4
    mov x4,BL
    mov BL,8
    mov y4,BL
    mov BL,'9'
    mov ch,BL
    LEA DX,tmpB
    mov AH,09
    int 21H
    mov DL,ch
    mov AH,02H
    int 21H
    LEA DX,tmpC
    mov AH,09
    int 21H
    mov AL,ch
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
    mov BL,y1
    mov x1,BL
    mov BL,3
    mov x2,BL
    mov BL,x1
    add BL,x2
    mov tmpD,BL
    mov BL,tmpD
    mov y2,BL
    mov AL,y4
    CMP AL,x4
    JG stepB
    JMP stepC
  stepB:
    mov AL,x1
    mov BH,2
    mul BH
    mov BL,1
    div BL
    mov tmpE,AL
    mov BL,tmpE
    mov x3,BL
    mov BL,x3
    add BL,10
    mov tmpF,BL
    mov BL,tmpF
    mov x3,BL
    JMP stepC
  stepC:
    mov AL,5
    CMP AL,y4
    JG stepD
    mov BL,x3
    sub BL,2
    mov tmpG,BL
    mov BL,tmpG
    mov y3,BL
    JMP stepE
  stepD:
    mov BL,y4
    add BL,1
    mov tmpH,BL
    mov BL,tmpH
    mov y4,BL
    JMP stepE
  stepE:
    LEA DX,tmpI
    mov AH,09
    int 21H
    mov AL,x1
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
    LEA DX,tmpJ
    mov AH,09
    int 21H
    mov AL,y1
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
    LEA DX,tmpK
    mov AH,09
    int 21H
    mov AL,x2
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepM
  stepL:
    mov DL,AL
    mov AH,2
    int 21H
  stepM:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpL
    mov AH,09
    int 21H
    mov AL,y2
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepO
  stepN:
    mov DL,AL
    mov AH,2
    int 21H
  stepO:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpM
    mov AH,09
    int 21H
    mov AL,x3
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepQ
  stepP:
    mov DL,AL
    mov AH,2
    int 21H
  stepQ:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpN
    mov AH,09
    int 21H
    mov AL,y3
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepS
  stepR:
    mov DL,AL
    mov AH,2
    int 21H
  stepS:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpO
    mov AH,09
    int 21H
    mov AL,x4
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepU
  stepT:
    mov DL,AL
    mov AH,2
    int 21H
  stepU:
    mov DL,BH
    mov AH,2
    int 21H
    LEA DX,tmpP
    mov AH,09
    int 21H
    mov AL,y4
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepW
  stepV:
    mov DL,AL
    mov AH,2
    int 21H
  stepW:
    mov DL,BH
    mov AH,2
    int 21H
    mov BL,6
    sub BL,3
    mov tmpQ,BL
    mov AL,tmpQ
    mov BH,x1
    mul BH
    mov BL,1
    div BL
    mov tmpR,AL
    mov BL,x2
    sub BL,1
    mov tmpS,BL
    mov AL,tmpS
    CBW
    mov BL,2
    div BL
    mov tmpT,AL
    mov AL,y4
    mov BH,x4
    mul BH
    mov BL,1
    div BL
    mov tmpU,AL
    mov BL,tmpU
    sub BL,x3
    mov tmpV,BL
    mov BL,tmpT
    add BL,tmpV
    mov tmpW,BL
    mov BL,tmpR
    add BL,tmpW
    mov tmpX,BL
    mov BL,tmpX
    mov y4,BL
    LEA DX,tmpY
    mov AH,09
    int 21H
    mov AL,y4
    CBW
    mov BL,10
    DIV BL
    mov BH,AH
    add BH,30H
    add AL,30H
    CMP AL,48
    JE stepY
  stepX:
    mov DL,AL
    mov AH,2
    int 21H
  stepY:
    mov DL,BH
    mov AH,2
    int 21H
    mov ax,4C00H
    int 21H
codesg ends
  end start

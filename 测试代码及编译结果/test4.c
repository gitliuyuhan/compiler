
/*
第四个测试程序 test4.c
*/

//混合测试
main()
{
	//定义整数类型
	int   x1,y1=2;
	int   x2,y2;
	int   x3,y3,x4=4,y4=8;

	//定义字符类型
	char  ch='9';

	printf("ch_char %c   ch_int %d",ch,ch);

	x1 = y1;
	x2 = 3;
	y2 = x1+x2;

	if(y4 > x4)
	{
		x3 = x1 * 2;
        x3 = x3 + 10;
	}

	if( 5 > y4 )
	{
		y4 = y4 + 1;
	}
	else
	{
		y3 = x3 -2;
	}
	printf("  x1=%d y1=%d x2=%d y2=%d x3=%d y3=%d x4=%d y4=%d",x1,y1,x2,y2,x3,y3,x4,y4);
    //四则混合运算
    y4 = (6-3)*x1 + (x2-1)/2 + y4*x4 -x3;
	printf("   result = %d",y4);
}

extern "C"{
#include <sys.h>	// Stm32_Clock_Init
#include <delay.h>	// delay_init
#include <usart.h>	// uart_init
}

int main(){
	u8 t = 0;
	Stm32_Clock_Init(336, 8, 2, 7);	// 初始化时钟为168Mhz
	delay_init(168);	// 初始化延时函数
	uart_init(84, 115200);	// 初始化串口为115200
	while(true){
		printf("t:%d\r\n", t);
		delay_ms(500);
		++t;
	}
	//return 0;
}

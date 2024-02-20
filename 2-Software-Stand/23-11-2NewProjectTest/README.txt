# 寄存器

```


#include "stm32f10x.h"

#define LED_Flag  1
int main(void)
{
    RCC->APB2ENR =0x00000010;
    
    GPIOC->CRH =0x00300000;
    
#if LED_Flag    
    GPIOC->ODR =0x00000000;
#else  
    GPIOC->ODR =0x00002000;

#endif    
    
    


    while(1)
        
    {
    
    
    }

}
```
# 库函数

```


```
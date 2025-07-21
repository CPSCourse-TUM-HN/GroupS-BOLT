#include "stm32f10x.h"
#include "OLED_Font.h"    // Font table for ASCII characters

/*------------------ Macros for Software I2C ------------------*/
#define OLED_W_SCL(x)    GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(x))
#define OLED_W_SDA(x)    GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(x))

/**
 * @brief Initializes GPIO pins for software I2C (PB8: SCL, PB9: SDA).
 */
void OLED_I2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    OLED_W_SCL(1);
    OLED_W_SDA(1);
}

/**
 * @brief Generates I2C start condition.
 */
void OLED_I2C_Start(void)
{
    OLED_W_SDA(1);
    OLED_W_SCL(1);
    OLED_W_SDA(0);
    OLED_W_SCL(0);
}

/**
 * @brief Generates I2C stop condition.
 */
void OLED_I2C_Stop(void)
{
    OLED_W_SDA(0);
    OLED_W_SCL(1);
    OLED_W_SDA(1);
}

/**
 * @brief Sends a single byte via I2C (MSB first).
 * @param Byte 8-bit data to send
 */
void OLED_I2C_SendByte(uint8_t Byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        OLED_W_SDA(Byte & (0x80 >> i));
        OLED_W_SCL(1);
        OLED_W_SCL(0);
    }

    OLED_W_SCL(1);  // Skip ACK handling
    OLED_W_SCL(0);
}

/**
 * @brief Writes a command byte to OLED.
 * @param Command Command to write
 */
void OLED_WriteCommand(uint8_t Command)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);     // Slave address
    OLED_I2C_SendByte(0x00);     // Command mode
    OLED_I2C_SendByte(Command);
    OLED_I2C_Stop();
}

/**
 * @brief Writes a data byte to OLED.
 * @param Data Data to write
 */
void OLED_WriteData(uint8_t Data)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);     // Slave address
    OLED_I2C_SendByte(0x40);     // Data mode
    OLED_I2C_SendByte(Data);
    OLED_I2C_Stop();
}

/**
 * @brief Sets OLED display cursor position.
 * @param Y Page address (0~7)
 * @param X Column address (0~127)
 */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_WriteCommand(0xB0 | Y);
    OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));
    OLED_WriteCommand(0x00 | (X & 0x0F));
}

/**
 * @brief Clears the OLED screen.
 */
void OLED_Clear(void)
{
    for (uint8_t j = 0; j < 8; j++)
    {
        OLED_SetCursor(j, 0);
        for (uint8_t i = 0; i < 128; i++)
        {
            OLED_WriteData(0x00);
        }
    }
}

/**
 * @brief Displays a single character (8x16 font).
 * @param Line Line number (1~4)
 * @param Column Column number (1~16)
 * @param Char ASCII character
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);
    for (uint8_t i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i]);
    }

    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);
    for (uint8_t i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);
    }
}

/**
 * @brief Displays a string on the OLED screen.
 * @param Line Starting line (1~4)
 * @param Column Starting column (1~16)
 * @param String Null-terminated string
 */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    for (uint8_t i = 0; String[i] != '\0'; i++)
    {
        OLED_ShowChar(Line, Column + i, String[i]);
    }
}

/**
 * @brief Computes power (X^Y).
 * @param X Base
 * @param Y Exponent
 * @retval Result of X raised to power Y
 */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--) Result *= X;
    return Result;
}

/**
 * @brief Displays an unsigned decimal number.
 * @param Line Line number (1~4)
 * @param Column Starting column (1~16)
 * @param Number Value to display (0~4294967295)
 * @param Length Number of digits to show
 */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t digit = Number / OLED_Pow(10, Length - i - 1) % 10;
        OLED_ShowChar(Line, Column + i, digit + '0');
    }
}

/**
 * @brief Displays a signed decimal number.
 * @param Line Line number (1~4)
 * @param Column Starting column (1~16)
 * @param Number Value to display (-2147483648 to 2147483647)
 * @param Length Number of digits (excluding sign)
 */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+');
        OLED_ShowNum(Line, Column + 1, Number, Length);
    }
    else
    {
        OLED_ShowChar(Line, Column, '-');
        OLED_ShowNum(Line, Column + 1, -Number, Length);
    }
}

/**
 * @brief Displays a hexadecimal number.
 * @param Line Line number (1~4)
 * @param Column Starting column (1~16)
 * @param Number Value to display
 * @param Length Number of digits (1~8)
 */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t digit = Number / OLED_Pow(16, Length - i - 1) % 16;
        OLED_ShowChar(Line, Column + i, digit < 10 ? (digit + '0') : (digit - 10 + 'A'));
    }
}

/**
 * @brief Displays a binary number.
 * @param Line Line number (1~4)
 * @param Column Starting column (1~16)
 * @param Number Value to display
 * @param Length Number of bits to show (1~16)
 */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t bit = Number / OLED_Pow(2, Length - i - 1) % 2;
        OLED_ShowChar(Line, Column + i, bit + '0');
    }
}

/**
 * @brief Initializes OLED display with default settings.
 */
void OLED_Init(void)
{
    // Power-on delay
    for (uint32_t i = 0; i < 1000; i++)
    {
        for (uint32_t j = 0; j < 1000; j++);
    }

    OLED_I2C_Init();

    OLED_WriteCommand(0xAE); // Display off
    OLED_WriteCommand(0xD5); OLED_WriteCommand(0x80); // Clock
    OLED_WriteCommand(0xA8); OLED_WriteCommand(0x3F); // MUX ratio
    OLED_WriteCommand(0xD3); OLED_WriteCommand(0x00); // Display offset
    OLED_WriteCommand(0x40);                         // Start line
    OLED_WriteCommand(0xA1);                         // Segment remap
    OLED_WriteCommand(0xC8);                         // COM scan direction
    OLED_WriteCommand(0xDA); OLED_WriteCommand(0x12);// COM pins
    OLED_WriteCommand(0x81); OLED_WriteCommand(0xCF);// Contrast
    OLED_WriteCommand(0xD9); OLED_WriteCommand(0xF1);// Pre-charge
    OLED_WriteCommand(0xDB); OLED_WriteCommand(0x30);// VCOM detect
    OLED_WriteCommand(0xA4);                         // Resume to RAM
    OLED_WriteCommand(0xA6);                         // Normal display
    OLED_WriteCommand(0x8D); OLED_WriteCommand(0x14);// Charge pump
    OLED_WriteCommand(0xAF);                         // Display ON

    OLED_Clear();
}
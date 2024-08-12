#ifndef __STC8A8K64D4_H__
#define __STC8A8K64D4_H__

/////////////////////////////////////////////////

//包含本头文件后,不用另外再包含"REG51.H"

sfr         P0          =           0x80;
sbit        P00         =           P0^0;
sbit        P01         =           P0^1;
sbit        P02         =           P0^2;
sbit        P03         =           P0^3;
sbit        P04         =           P0^4;
sbit        P05         =           P0^5;
sbit        P06         =           P0^6;
sbit        P07         =           P0^7;
sfr         SP          =           0x81;
sfr         DPL         =           0x82;
sfr         DPH         =           0x83;
sfr         S4CON       =           0x84;
sfr         S4BUF       =           0x85;
sfr         PCON        =           0x87;
sfr         TCON        =           0x88;
sbit        TF1         =           TCON^7;
sbit        TR1         =           TCON^6;
sbit        TF0         =           TCON^5;
sbit        TR0         =           TCON^4;
sbit        IE1         =           TCON^3;
sbit        IT1         =           TCON^2;
sbit        IE0         =           TCON^1;
sbit        IT0         =           TCON^0;
sfr         TMOD        =           0x89;
sfr         TL0         =           0x8a;
sfr         TL1         =           0x8b;
sfr         TH0         =           0x8c;
sfr         TH1         =           0x8d;
sfr         AUXR        =           0x8e;
sfr         INTCLKO     =           0x8f;
sfr         P1          =           0x90;
sbit        P10         =           P1^0;
sbit        P11         =           P1^1;
sbit        P12         =           P1^2;
sbit        P13         =           P1^3;
sbit        P14         =           P1^4;
sbit        P15         =           P1^5;
sbit        P16         =           P1^6;
sbit        P17         =           P1^7;
sfr         P1M1        =           0x91;
sfr         P1M0        =           0x92;
sfr         P0M1        =           0x93;
sfr         P0M0        =           0x94;
sfr         P2M1        =           0x95;
sfr         P2M0        =           0x96;
sfr         SCON        =           0x98;
sbit        SM0         =           SCON^7;
sbit        SM1         =           SCON^6;
sbit        SM2         =           SCON^5;
sbit        REN         =           SCON^4;
sbit        TB8         =           SCON^3;
sbit        RB8         =           SCON^2;
sbit        TI          =           SCON^1;
sbit        RI          =           SCON^0;
sfr         SBUF        =           0x99;
sfr         S2CON       =           0x9a;
sfr         S2BUF       =           0x9b;
sfr         IRCBAND     =           0x9d;
sfr         LIRTRIM     =           0x9e;
sfr         IRTRIM      =           0x9f;
sfr         P2          =           0xa0;
sbit        P20         =           P2^0;
sbit        P21         =           P2^1;
sbit        P22         =           P2^2;
sbit        P23         =           P2^3;
sbit        P24         =           P2^4;
sbit        P25         =           P2^5;
sbit        P26         =           P2^6;
sbit        P27         =           P2^7;
sfr         BUS_SPEED   =           0xa1;
sfr         P_SW1       =           0xa2;
sfr         IE          =           0xa8;
sbit        EA          =           IE^7;
sbit        ELVD        =           IE^6;
sbit        EADC        =           IE^5;
sbit        ES          =           IE^4;
sbit        ET1         =           IE^3;
sbit        EX1         =           IE^2;
sbit        ET0         =           IE^1;
sbit        EX0         =           IE^0;
sfr         SADDR       =           0xa9;
sfr         WKTCL       =           0xaa;
sfr         WKTCH       =           0xab;
sfr         S3CON       =           0xac;
sfr         S3BUF       =           0xad;
sfr         TA          =           0xae;
sfr         IE2         =           0xaf;
sfr         P3          =           0xb0;
sbit        P30         =           P3^0;
sbit        P31         =           P3^1;
sbit        P32         =           P3^2;
sbit        P33         =           P3^3;
sbit        P34         =           P3^4;
sbit        P35         =           P3^5;
sbit        P36         =           P3^6;
sbit        P37         =           P3^7;
sfr         P3M1        =           0xb1;
sfr         P3M0        =           0xb2;
sfr         P4M1        =           0xb3;
sfr         P4M0        =           0xb4;
sfr         IP2         =           0xb5;
sfr         IP2H        =           0xb6;
sfr         IPH         =           0xb7;
sfr         IP          =           0xb8;
sbit        PPCA        =           IP^7;
sbit        PLVD        =           IP^6;
sbit        PADC        =           IP^5;
sbit        PS          =           IP^4;
sbit        PT1         =           IP^3;
sbit        PX1         =           IP^2;
sbit        PT0         =           IP^1;
sbit        PX0         =           IP^0;
sfr         SADEN       =           0xb9;
sfr         P_SW2       =           0xba;
sfr         ADC_CONTR   =           0xbc;
sfr         ADC_RES     =           0xbd;
sfr         ADC_RESL    =           0xbe;
sfr         P4          =           0xc0;
sbit        P40         =           P4^0;
sbit        P41         =           P4^1;
sbit        P42         =           P4^2;
sbit        P43         =           P4^3;
sbit        P44         =           P4^4;
sbit        P45         =           P4^5;
sbit        P46         =           P4^6;
sbit        P47         =           P4^7;
sfr         WDT_CONTR   =           0xc1;
sfr         IAP_DATA    =           0xc2;
sfr         IAP_ADDRH   =           0xc3;
sfr         IAP_ADDRL   =           0xc4;
sfr         IAP_CMD     =           0xc5;
sfr         IAP_TRIG    =           0xc6;
sfr         IAP_CONTR   =           0xc7;
sfr         P5          =           0xc8;
sbit        P50         =           P5^0;
sbit        P51         =           P5^1;
sbit        P52         =           P5^2;
sbit        P53         =           P5^3;
sbit        P54         =           P5^4;
sbit        P55         =           P5^5;
sbit        P56         =           P5^6;
sbit        P57         =           P5^7;
sfr         P5M1        =           0xc9;
sfr         P5M0        =           0xca;
sfr         P6M1        =           0xcb;
sfr         P6M0        =           0xcc;
sfr         SPSTAT      =           0xcd;
sfr         SPCTL       =           0xce;
sfr         SPDAT       =           0xcf;
sfr         PSW         =           0xd0;
sbit        CY          =           PSW^7;
sbit        AC          =           PSW^6;
sbit        F0          =           PSW^5;
sbit        RS1         =           PSW^4;
sbit        RS0         =           PSW^3;
sbit        OV          =           PSW^2;
sbit        P           =           PSW^0;
sfr         T4T3M       =           0xd1;
sfr         T4H         =           0xd2;
sfr         T4L         =           0xd3;
sfr         T3H         =           0xd4;
sfr         T3L         =           0xd5;
sfr         T2H         =           0xd6;
sfr         T2L         =           0xd7;
sfr         CCON        =           0xd8;
sbit        CF          =           CCON^7;
sbit        CR          =           CCON^6;
sbit        CCF3        =           CCON^3;
sbit        CCF2        =           CCON^2;
sbit        CCF1        =           CCON^1;
sbit        CCF0        =           CCON^0;
sfr         CMOD        =           0xd9;
sfr         CCAPM0      =           0xda;
sfr         CCAPM1      =           0xdb;
sfr         CCAPM2      =           0xdc;
sfr         ADCCFG      =           0xde;
sfr         IP3         =           0xdf;
sfr         ACC         =           0xe0;
sfr         P7M1        =           0xe1;
sfr         P7M0        =           0xe2;
sfr         DPS         =           0xe3;
sfr         DPL1        =           0xe4;
sfr         DPH1        =           0xe5;
sfr         CMPCR1      =           0xe6;
sfr         CMPCR2      =           0xe7;
sfr         P6          =           0xe8;
sbit        P60         =           P6^0;
sbit        P61         =           P6^1;
sbit        P62         =           P6^2;
sbit        P63         =           P6^3;
sbit        P64         =           P6^4;
sbit        P65         =           P6^5;
sbit        P66         =           P6^6;
sbit        P67         =           P6^7;
sfr         CL          =           0xe9;
sfr         CCAP0L      =           0xea;
sfr         CCAP1L      =           0xeb;
sfr         CCAP2L      =           0xec;
sfr         IP3H        =           0xee;
sfr         AUXINTIF    =           0xef;
sfr         B           =           0xf0;
sfr         PWMSET      =           0xf1;
sfr         PCA_PWM0    =           0xf2;
sfr         PCA_PWM1    =           0xf3;
sfr         PCA_PWM2    =           0xf4;
sfr         IAP_TPS     =           0xf5;
sfr         PWMCFG      =           0xf6;
sfr         P7          =           0xf8;
sbit        P70         =           P7^0;
sbit        P71         =           P7^1;
sbit        P72         =           P7^2;
sbit        P73         =           P7^3;
sbit        P74         =           P7^4;
sbit        P75         =           P7^5;
sbit        P76         =           P7^6;
sbit        P77         =           P7^7;
sfr         CH          =           0xf9;
sfr         CCAP0H      =           0xfa;
sfr         CCAP1H      =           0xfb;
sfr         CCAP2H      =           0xfc;
sfr         RSTCFG      =           0xff;

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写

/////////////////////////////////////////////////
//FF00H-FFFFH
/////////////////////////////////////////////////


#define     PWMC                    (*(unsigned int  volatile xdata *)0xff00)
#define     PWMCH                   (*(unsigned char volatile xdata *)0xff00)
#define     PWMCL                   (*(unsigned char volatile xdata *)0xff01)
#define     PWMCKS                  (*(unsigned char volatile xdata *)0xff02)
#define     PWMTADC                 (*(unsigned int  volatile xdata *)0xff03)
#define     PWMTADCH                (*(unsigned char volatile xdata *)0xff03)
#define     PWMTADCL                (*(unsigned char volatile xdata *)0xff04)
#define     PWMIF                   (*(unsigned char volatile xdata *)0xff05)
#define     PWMFDCR                 (*(unsigned char volatile xdata *)0xff06)
#define     PWMDELSEL               (*(unsigned char volatile xdata *)0xff07)
#define     PWM0T1                  (*(unsigned int  volatile xdata *)0xff10)
#define     PWM0T1H                 (*(unsigned char volatile xdata *)0xff10)
#define     PWM0T1L                 (*(unsigned char volatile xdata *)0xff11)
#define     PWM0T2                  (*(unsigned int  volatile xdata *)0xff12)
#define     PWM0T2H                 (*(unsigned char volatile xdata *)0xff12)
#define     PWM0T2L                 (*(unsigned char volatile xdata *)0xff13)
#define     PWM0CR                  (*(unsigned char volatile xdata *)0xff14)
#define     PWM0HLD                 (*(unsigned char volatile xdata *)0xff15)
#define     PWM1T1                  (*(unsigned int  volatile xdata *)0xff18)
#define     PWM1T1H                 (*(unsigned char volatile xdata *)0xff18)
#define     PWM1T1L                 (*(unsigned char volatile xdata *)0xff19)
#define     PWM1T2                  (*(unsigned int  volatile xdata *)0xff1a)
#define     PWM1T2H                 (*(unsigned char volatile xdata *)0xff1a)
#define     PWM1T2L                 (*(unsigned char volatile xdata *)0xff1b)
#define     PWM1CR                  (*(unsigned char volatile xdata *)0xff1c)
#define     PWM1HLD                 (*(unsigned char volatile xdata *)0xff1d)
#define     PWM2T1                  (*(unsigned int  volatile xdata *)0xff20)
#define     PWM2T1H                 (*(unsigned char volatile xdata *)0xff20)
#define     PWM2T1L                 (*(unsigned char volatile xdata *)0xff21)
#define     PWM2T2                  (*(unsigned int  volatile xdata *)0xff22)
#define     PWM2T2H                 (*(unsigned char volatile xdata *)0xff22)
#define     PWM2T2L                 (*(unsigned char volatile xdata *)0xff23)
#define     PWM2CR                  (*(unsigned char volatile xdata *)0xff24)
#define     PWM2HLD                 (*(unsigned char volatile xdata *)0xff25)
#define     PWM3T1                  (*(unsigned int  volatile xdata *)0xff28)
#define     PWM3T1H                 (*(unsigned char volatile xdata *)0xff28)
#define     PWM3T1L                 (*(unsigned char volatile xdata *)0xff29)
#define     PWM3T2                  (*(unsigned int  volatile xdata *)0xff2a)
#define     PWM3T2H                 (*(unsigned char volatile xdata *)0xff2a)
#define     PWM3T2L                 (*(unsigned char volatile xdata *)0xff2b)
#define     PWM3CR                  (*(unsigned char volatile xdata *)0xff2c)
#define     PWM3HLD                 (*(unsigned char volatile xdata *)0xff2d)
#define     PWM4T1                  (*(unsigned int  volatile xdata *)0xff30)
#define     PWM4T1H                 (*(unsigned char volatile xdata *)0xff30)
#define     PWM4T1L                 (*(unsigned char volatile xdata *)0xff31)
#define     PWM4T2                  (*(unsigned int  volatile xdata *)0xff32)
#define     PWM4T2H                 (*(unsigned char volatile xdata *)0xff32)
#define     PWM4T2L                 (*(unsigned char volatile xdata *)0xff33)
#define     PWM4CR                  (*(unsigned char volatile xdata *)0xff34)
#define     PWM4HLD                 (*(unsigned char volatile xdata *)0xff35)
#define     PWM5T1                  (*(unsigned int  volatile xdata *)0xff38)
#define     PWM5T1H                 (*(unsigned char volatile xdata *)0xff38)
#define     PWM5T1L                 (*(unsigned char volatile xdata *)0xff39)
#define     PWM5T2                  (*(unsigned int  volatile xdata *)0xff3a)
#define     PWM5T2H                 (*(unsigned char volatile xdata *)0xff3a)
#define     PWM5T2L                 (*(unsigned char volatile xdata *)0xff3b)
#define     PWM5CR                  (*(unsigned char volatile xdata *)0xff3c)
#define     PWM5HLD                 (*(unsigned char volatile xdata *)0xff3d)
#define     PWM6T1                  (*(unsigned int  volatile xdata *)0xff40)
#define     PWM6T1H                 (*(unsigned char volatile xdata *)0xff40)
#define     PWM6T1L                 (*(unsigned char volatile xdata *)0xff41)
#define     PWM6T2                  (*(unsigned int  volatile xdata *)0xff42)
#define     PWM6T2H                 (*(unsigned char volatile xdata *)0xff42)
#define     PWM6T2L                 (*(unsigned char volatile xdata *)0xff43)
#define     PWM6CR                  (*(unsigned char volatile xdata *)0xff44)
#define     PWM6HLD                 (*(unsigned char volatile xdata *)0xff45)
#define     PWM7T1                  (*(unsigned int  volatile xdata *)0xff48)
#define     PWM7T1H                 (*(unsigned char volatile xdata *)0xff48)
#define     PWM7T1L                 (*(unsigned char volatile xdata *)0xff49)
#define     PWM7T2                  (*(unsigned int  volatile xdata *)0xff4a)
#define     PWM7T2H                 (*(unsigned char volatile xdata *)0xff4a)
#define     PWM7T2L                 (*(unsigned char volatile xdata *)0xff4b)
#define     PWM7CR                  (*(unsigned char volatile xdata *)0xff4c)
#define     PWM7HLD                 (*(unsigned char volatile xdata *)0xff4d)

/////////////////////////////////////////////////
//FE00H-FEFFH
/////////////////////////////////////////////////

#define     CLKSEL                  (*(unsigned char volatile xdata *)0xfe00)
#define     CLKDIV                  (*(unsigned char volatile xdata *)0xfe01)
#define     IRC24MCR                (*(unsigned char volatile xdata *)0xfe02)
#define     XOSCCR                  (*(unsigned char volatile xdata *)0xfe03)
#define     IRC32KCR                (*(unsigned char volatile xdata *)0xfe04)
#define     MCLKOCR                 (*(unsigned char volatile xdata *)0xfe05)
#define     IRCDB                   (*(unsigned char volatile xdata *)0xfe06)

#define     P0PU                    (*(unsigned char volatile xdata *)0xfe10)
#define     P1PU                    (*(unsigned char volatile xdata *)0xfe11)
#define     P2PU                    (*(unsigned char volatile xdata *)0xfe12)
#define     P3PU                    (*(unsigned char volatile xdata *)0xfe13)
#define     P4PU                    (*(unsigned char volatile xdata *)0xfe14)
#define     P5PU                    (*(unsigned char volatile xdata *)0xfe15)
#define     P6PU                    (*(unsigned char volatile xdata *)0xfe16)
#define     P7PU                    (*(unsigned char volatile xdata *)0xfe17)
#define     P0NCS                   (*(unsigned char volatile xdata *)0xfe18)
#define     P1NCS                   (*(unsigned char volatile xdata *)0xfe19)
#define     P2NCS                   (*(unsigned char volatile xdata *)0xfe1a)
#define     P3NCS                   (*(unsigned char volatile xdata *)0xfe1b)
#define     P4NCS                   (*(unsigned char volatile xdata *)0xfe1c)
#define     P5NCS                   (*(unsigned char volatile xdata *)0xfe1d)
#define     P6NCS                   (*(unsigned char volatile xdata *)0xfe1e)
#define     P7NCS                   (*(unsigned char volatile xdata *)0xfe1f)
#define     P0SR                    (*(unsigned char volatile xdata *)0xfe20)
#define     P1SR                    (*(unsigned char volatile xdata *)0xfe21)
#define     P2SR                    (*(unsigned char volatile xdata *)0xfe22)
#define     P3SR                    (*(unsigned char volatile xdata *)0xfe23)
#define     P4SR                    (*(unsigned char volatile xdata *)0xfe24)
#define     P5SR                    (*(unsigned char volatile xdata *)0xfe25)
#define     P6SR                    (*(unsigned char volatile xdata *)0xfe26)
#define     P7SR                    (*(unsigned char volatile xdata *)0xfe27)
#define     P0DR                    (*(unsigned char volatile xdata *)0xfe28)
#define     P1DR                    (*(unsigned char volatile xdata *)0xfe29)
#define     P2DR                    (*(unsigned char volatile xdata *)0xfe2a)
#define     P3DR                    (*(unsigned char volatile xdata *)0xfe2b)
#define     P4DR                    (*(unsigned char volatile xdata *)0xfe2c)
#define     P5DR                    (*(unsigned char volatile xdata *)0xfe2d)
#define     P6DR                    (*(unsigned char volatile xdata *)0xfe2e)
#define     P7DR                    (*(unsigned char volatile xdata *)0xfe2f)
#define     P0IE                    (*(unsigned char volatile xdata *)0xfe30)
#define     P1IE                    (*(unsigned char volatile xdata *)0xfe31)
#define     P2IE                    (*(unsigned char volatile xdata *)0xfe32)
#define     P3IE                    (*(unsigned char volatile xdata *)0xfe33)
#define     P4IE                    (*(unsigned char volatile xdata *)0xfe34)
#define     P5IE                    (*(unsigned char volatile xdata *)0xfe35)
#define     P6IE                    (*(unsigned char volatile xdata *)0xfe36)
#define     P7IE                    (*(unsigned char volatile xdata *)0xfe37)

#define     LCMIFCFG                (*(unsigned char volatile xdata *)0xfe50)
#define     LCMIFCFG2               (*(unsigned char volatile xdata *)0xfe51)
#define     LCMIFCR                 (*(unsigned char volatile xdata *)0xfe52)
#define     LCMIFSTA                (*(unsigned char volatile xdata *)0xfe53)
#define     LCMIFDATL               (*(unsigned char volatile xdata *)0xfe54)
#define     LCMIFDATH               (*(unsigned char volatile xdata *)0xfe55)

#define     I2CCFG                  (*(unsigned char volatile xdata *)0xfe80)
#define     I2CMSCR                 (*(unsigned char volatile xdata *)0xfe81)
#define     I2CMSST                 (*(unsigned char volatile xdata *)0xfe82)
#define     I2CSLCR                 (*(unsigned char volatile xdata *)0xfe83)
#define     I2CSLST                 (*(unsigned char volatile xdata *)0xfe84)
#define     I2CSLADR                (*(unsigned char volatile xdata *)0xfe85)
#define     I2CTXD                  (*(unsigned char volatile xdata *)0xfe86)
#define     I2CRXD                  (*(unsigned char volatile xdata *)0xfe87)
#define     I2CMSAUX                (*(unsigned char volatile xdata *)0xfe88)

#define     TM2PS                   (*(unsigned char volatile xdata *)0xfea2)
#define     TM3PS                   (*(unsigned char volatile xdata *)0xfea3)
#define     TM4PS                   (*(unsigned char volatile xdata *)0xfea4)
#define     ADCTIM                  (*(unsigned char volatile xdata *)0xfea8)
#define     ADCEXCFG                (*(unsigned char volatile xdata *)0xfead)
#define     CMPEXCFG                (*(unsigned char volatile xdata *)0xfeae)

/////////////////////////////////////////////////
//FD00H-FDFFH
/////////////////////////////////////////////////

#define     P0INTE                  (*(unsigned char volatile xdata *)0xfd00)
#define     P1INTE                  (*(unsigned char volatile xdata *)0xfd01)
#define     P2INTE                  (*(unsigned char volatile xdata *)0xfd02)
#define     P3INTE                  (*(unsigned char volatile xdata *)0xfd03)
#define     P4INTE                  (*(unsigned char volatile xdata *)0xfd04)
#define     P5INTE                  (*(unsigned char volatile xdata *)0xfd05)
#define     P6INTE                  (*(unsigned char volatile xdata *)0xfd06)
#define     P7INTE                  (*(unsigned char volatile xdata *)0xfd07)
#define     P0INTF                  (*(unsigned char volatile xdata *)0xfd10)
#define     P1INTF                  (*(unsigned char volatile xdata *)0xfd11)
#define     P2INTF                  (*(unsigned char volatile xdata *)0xfd12)
#define     P3INTF                  (*(unsigned char volatile xdata *)0xfd13)
#define     P4INTF                  (*(unsigned char volatile xdata *)0xfd14)
#define     P5INTF                  (*(unsigned char volatile xdata *)0xfd15)
#define     P6INTF                  (*(unsigned char volatile xdata *)0xfd16)
#define     P7INTF                  (*(unsigned char volatile xdata *)0xfd17)
#define     P0IM0                   (*(unsigned char volatile xdata *)0xfd20)
#define     P1IM0                   (*(unsigned char volatile xdata *)0xfd21)
#define     P2IM0                   (*(unsigned char volatile xdata *)0xfd22)
#define     P3IM0                   (*(unsigned char volatile xdata *)0xfd23)
#define     P4IM0                   (*(unsigned char volatile xdata *)0xfd24)
#define     P5IM0                   (*(unsigned char volatile xdata *)0xfd25)
#define     P6IM0                   (*(unsigned char volatile xdata *)0xfd26)
#define     P7IM0                   (*(unsigned char volatile xdata *)0xfd27)
#define     P0IM1                   (*(unsigned char volatile xdata *)0xfd30)
#define     P1IM1                   (*(unsigned char volatile xdata *)0xfd31)
#define     P2IM1                   (*(unsigned char volatile xdata *)0xfd32)
#define     P3IM1                   (*(unsigned char volatile xdata *)0xfd33)
#define     P4IM1                   (*(unsigned char volatile xdata *)0xfd34)
#define     P5IM1                   (*(unsigned char volatile xdata *)0xfd35)
#define     P6IM1                   (*(unsigned char volatile xdata *)0xfd36)
#define     P7IM1                   (*(unsigned char volatile xdata *)0xfd37)
#define     P0WKUE                  (*(unsigned char volatile xdata *)0xfd40)
#define     P1WKUE                  (*(unsigned char volatile xdata *)0xfd41)
#define     P2WKUE                  (*(unsigned char volatile xdata *)0xfd42)
#define     P3WKUE                  (*(unsigned char volatile xdata *)0xfd43)
#define     P4WKUE                  (*(unsigned char volatile xdata *)0xfd44)
#define     P5WKUE                  (*(unsigned char volatile xdata *)0xfd45)
#define     P6WKUE                  (*(unsigned char volatile xdata *)0xfd46)
#define     P7WKUE                  (*(unsigned char volatile xdata *)0xfd47)

#define     CCAPM3                  (*(unsigned char volatile xdata *)0xfd54)
#define     CCAP3L                  (*(unsigned char volatile xdata *)0xfd55)
#define     CCAP3H                  (*(unsigned char volatile xdata *)0xfd56)
#define     PCA_PWM3                (*(unsigned char volatile xdata *)0xfd57)

#define     PIN_IP                  (*(unsigned char volatile xdata *)0xfd60)
#define     PIN_IPH                 (*(unsigned char volatile xdata *)0xfd61)

#define     CHIPID0                 (*(unsigned char volatile xdata *)0xfde0)
#define     CHIPID1                 (*(unsigned char volatile xdata *)0xfde1)
#define     CHIPID2                 (*(unsigned char volatile xdata *)0xfde2)
#define     CHIPID3                 (*(unsigned char volatile xdata *)0xfde3)
#define     CHIPID4                 (*(unsigned char volatile xdata *)0xfde4)
#define     CHIPID5                 (*(unsigned char volatile xdata *)0xfde5)
#define     CHIPID6                 (*(unsigned char volatile xdata *)0xfde6)
#define     CHIPID7                 (*(unsigned char volatile xdata *)0xfde7)
#define     CHIPID8                 (*(unsigned char volatile xdata *)0xfde8)
#define     CHIPID9                 (*(unsigned char volatile xdata *)0xfde9)
#define     CHIPID10                (*(unsigned char volatile xdata *)0xfdea)
#define     CHIPID11                (*(unsigned char volatile xdata *)0xfdeb)
#define     CHIPID12                (*(unsigned char volatile xdata *)0xfdec)
#define     CHIPID13                (*(unsigned char volatile xdata *)0xfded)
#define     CHIPID14                (*(unsigned char volatile xdata *)0xfdee)
#define     CHIPID15                (*(unsigned char volatile xdata *)0xfdef)
#define     CHIPID16                (*(unsigned char volatile xdata *)0xfdf0)
#define     CHIPID17                (*(unsigned char volatile xdata *)0xfdf1)
#define     CHIPID18                (*(unsigned char volatile xdata *)0xfdf2)
#define     CHIPID19                (*(unsigned char volatile xdata *)0xfdf3)
#define     CHIPID20                (*(unsigned char volatile xdata *)0xfdf4)
#define     CHIPID21                (*(unsigned char volatile xdata *)0xfdf5)
#define     CHIPID22                (*(unsigned char volatile xdata *)0xfdf6)
#define     CHIPID23                (*(unsigned char volatile xdata *)0xfdf7)
#define     CHIPID24                (*(unsigned char volatile xdata *)0xfdf8)
#define     CHIPID25                (*(unsigned char volatile xdata *)0xfdf9)
#define     CHIPID26                (*(unsigned char volatile xdata *)0xfdfa)
#define     CHIPID27                (*(unsigned char volatile xdata *)0xfdfb)
#define     CHIPID28                (*(unsigned char volatile xdata *)0xfdfc)
#define     CHIPID29                (*(unsigned char volatile xdata *)0xfdfd)
#define     CHIPID30                (*(unsigned char volatile xdata *)0xfdfe)
#define     CHIPID31                (*(unsigned char volatile xdata *)0xfdff)

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////

#define     MD3                     (*(unsigned char volatile xdata *)0xfcf0)
#define     MD2                     (*(unsigned char volatile xdata *)0xfcf1)
#define     MD1                     (*(unsigned char volatile xdata *)0xfcf2)
#define     MD0                     (*(unsigned char volatile xdata *)0xfcf3)
#define     MD5                     (*(unsigned char volatile xdata *)0xfcf4)
#define     MD4                     (*(unsigned char volatile xdata *)0xfcf5)
#define     ARCON                   (*(unsigned char volatile xdata *)0xfcf6)
#define     OPCON                   (*(unsigned char volatile xdata *)0xfcf7)

/////////////////////////////////////////////////
//FB00H-FBFFH
/////////////////////////////////////////////////


/////////////////////////////////////////////////
//FA00H-FAFFH
/////////////////////////////////////////////////

#define     DMA_ADC_CFG             (*(unsigned char volatile xdata *)0xfa10)
#define     DMA_ADC_CR              (*(unsigned char volatile xdata *)0xfa11)
#define     DMA_ADC_STA             (*(unsigned char volatile xdata *)0xfa12)
#define     DMA_ADC_RXA             (*(unsigned  int volatile xdata *)0xfa17)
#define     DMA_ADC_RXAH            (*(unsigned char volatile xdata *)0xfa17)
#define     DMA_ADC_RXAL            (*(unsigned char volatile xdata *)0xfa18)
#define     DMA_ADC_CFG2            (*(unsigned char volatile xdata *)0xfa19)
#define     DMA_ADC_CHSW0           (*(unsigned char volatile xdata *)0xfa1a)
#define     DMA_ADC_CHSW1           (*(unsigned char volatile xdata *)0xfa1b)

#define     DMA_SPI_CFG             (*(unsigned char volatile xdata *)0xfa20)
#define     DMA_SPI_CR              (*(unsigned char volatile xdata *)0xfa21)
#define     DMA_SPI_STA             (*(unsigned char volatile xdata *)0xfa22)
#define     DMA_SPI_AMT             (*(unsigned char volatile xdata *)0xfa23)
#define     DMA_SPI_DONE            (*(unsigned char volatile xdata *)0xfa24)
#define     DMA_SPI_TXA             (*(unsigned  int volatile xdata *)0xfa25)
#define     DMA_SPI_TXAH            (*(unsigned char volatile xdata *)0xfa25)
#define     DMA_SPI_TXAL            (*(unsigned char volatile xdata *)0xfa26)
#define     DMA_SPI_RXA             (*(unsigned  int volatile xdata *)0xfa27)
#define     DMA_SPI_RXAH            (*(unsigned char volatile xdata *)0xfa27)
#define     DMA_SPI_RXAL            (*(unsigned char volatile xdata *)0xfa28)
#define     DMA_SPI_CFG2            (*(unsigned char volatile xdata *)0xfa29)

#define     DMA_UR1T_CFG            (*(unsigned char volatile xdata *)0xfa30)
#define     DMA_UR1T_CR             (*(unsigned char volatile xdata *)0xfa31)
#define     DMA_UR1T_STA            (*(unsigned char volatile xdata *)0xfa32)
#define     DMA_UR1T_AMT            (*(unsigned char volatile xdata *)0xfa33)
#define     DMA_UR1T_DONE           (*(unsigned char volatile xdata *)0xfa34)
#define     DMA_UR1T_TXA            (*(unsigned  int volatile xdata *)0xfa35)
#define     DMA_UR1T_TXAH           (*(unsigned char volatile xdata *)0xfa35)
#define     DMA_UR1T_TXAL           (*(unsigned char volatile xdata *)0xfa36)
#define     DMA_UR1R_CFG            (*(unsigned char volatile xdata *)0xfa38)
#define     DMA_UR1R_CR             (*(unsigned char volatile xdata *)0xfa39)
#define     DMA_UR1R_STA            (*(unsigned char volatile xdata *)0xfa3a)
#define     DMA_UR1R_AMT            (*(unsigned char volatile xdata *)0xfa3b)
#define     DMA_UR1R_DONE           (*(unsigned char volatile xdata *)0xfa3c)
#define     DMA_UR1R_RXA            (*(unsigned  int volatile xdata *)0xfa3d)
#define     DMA_UR1R_RXAH           (*(unsigned char volatile xdata *)0xfa3d)
#define     DMA_UR1R_RXAL           (*(unsigned char volatile xdata *)0xfa3e)

#define     DMA_UR2T_CFG            (*(unsigned char volatile xdata *)0xfa40)
#define     DMA_UR2T_CR             (*(unsigned char volatile xdata *)0xfa41)
#define     DMA_UR2T_STA            (*(unsigned char volatile xdata *)0xfa42)
#define     DMA_UR2T_AMT            (*(unsigned char volatile xdata *)0xfa43)
#define     DMA_UR2T_DONE           (*(unsigned char volatile xdata *)0xfa44)
#define     DMA_UR2T_TXA            (*(unsigned  int volatile xdata *)0xfa45)
#define     DMA_UR2T_TXAH           (*(unsigned char volatile xdata *)0xfa45)
#define     DMA_UR2T_TXAL           (*(unsigned char volatile xdata *)0xfa46)
#define     DMA_UR2R_CFG            (*(unsigned char volatile xdata *)0xfa48)
#define     DMA_UR2R_CR             (*(unsigned char volatile xdata *)0xfa49)
#define     DMA_UR2R_STA            (*(unsigned char volatile xdata *)0xfa4a)
#define     DMA_UR2R_AMT            (*(unsigned char volatile xdata *)0xfa4b)
#define     DMA_UR2R_DONE           (*(unsigned char volatile xdata *)0xfa4c)
#define     DMA_UR2R_RXA            (*(unsigned  int volatile xdata *)0xfa4d)
#define     DMA_UR2R_RXAH           (*(unsigned char volatile xdata *)0xfa4d)
#define     DMA_UR2R_RXAL           (*(unsigned char volatile xdata *)0xfa4e)

#define     DMA_UR3T_CFG            (*(unsigned char volatile xdata *)0xfa50)
#define     DMA_UR3T_CR             (*(unsigned char volatile xdata *)0xfa51)
#define     DMA_UR3T_STA            (*(unsigned char volatile xdata *)0xfa52)
#define     DMA_UR3T_AMT            (*(unsigned char volatile xdata *)0xfa53)
#define     DMA_UR3T_DONE           (*(unsigned char volatile xdata *)0xfa54)
#define     DMA_UR3T_TXA            (*(unsigned  int volatile xdata *)0xfa55)
#define     DMA_UR3T_TXAH           (*(unsigned char volatile xdata *)0xfa55)
#define     DMA_UR3T_TXAL           (*(unsigned char volatile xdata *)0xfa56)
#define     DMA_UR3R_CFG            (*(unsigned char volatile xdata *)0xfa58)
#define     DMA_UR3R_CR             (*(unsigned char volatile xdata *)0xfa59)
#define     DMA_UR3R_STA            (*(unsigned char volatile xdata *)0xfa5a)
#define     DMA_UR3R_AMT            (*(unsigned char volatile xdata *)0xfa5b)
#define     DMA_UR3R_DONE           (*(unsigned char volatile xdata *)0xfa5c)
#define     DMA_UR3R_RXA            (*(unsigned  int volatile xdata *)0xfa5d)
#define     DMA_UR3R_RXAH           (*(unsigned char volatile xdata *)0xfa5d)
#define     DMA_UR3R_RXAL           (*(unsigned char volatile xdata *)0xfa5e)

#define     DMA_UR4T_CFG            (*(unsigned char volatile xdata *)0xfa60)
#define     DMA_UR4T_CR             (*(unsigned char volatile xdata *)0xfa61)
#define     DMA_UR4T_STA            (*(unsigned char volatile xdata *)0xfa62)
#define     DMA_UR4T_AMT            (*(unsigned char volatile xdata *)0xfa63)
#define     DMA_UR4T_DONE           (*(unsigned char volatile xdata *)0xfa64)
#define     DMA_UR4T_TXA            (*(unsigned  int volatile xdata *)0xfa65)
#define     DMA_UR4T_TXAH           (*(unsigned char volatile xdata *)0xfa65)
#define     DMA_UR4T_TXAL           (*(unsigned char volatile xdata *)0xfa66)
#define     DMA_UR4R_CFG            (*(unsigned char volatile xdata *)0xfa68)
#define     DMA_UR4R_CR             (*(unsigned char volatile xdata *)0xfa69)
#define     DMA_UR4R_STA            (*(unsigned char volatile xdata *)0xfa6a)
#define     DMA_UR4R_AMT            (*(unsigned char volatile xdata *)0xfa6b)
#define     DMA_UR4R_DONE           (*(unsigned char volatile xdata *)0xfa6c)
#define     DMA_UR4R_RXA            (*(unsigned  int volatile xdata *)0xfa6d)
#define     DMA_UR4R_RXAH           (*(unsigned char volatile xdata *)0xfa6d)
#define     DMA_UR4R_RXAL           (*(unsigned char volatile xdata *)0xfa6e)

#define     DMA_LCM_CFG             (*(unsigned char volatile xdata *)0xfa70)
#define     DMA_LCM_CR              (*(unsigned char volatile xdata *)0xfa71)
#define     DMA_LCM_STA             (*(unsigned char volatile xdata *)0xfa72)
#define     DMA_LCM_AMT             (*(unsigned char volatile xdata *)0xfa73)
#define     DMA_LCM_DONE            (*(unsigned char volatile xdata *)0xfa74)
#define     DMA_LCM_TXA             (*(unsigned  int volatile xdata *)0xfa75)
#define     DMA_LCM_TXAH            (*(unsigned char volatile xdata *)0xfa75)
#define     DMA_LCM_TXAL            (*(unsigned char volatile xdata *)0xfa76)
#define     DMA_LCM_RXA             (*(unsigned  int volatile xdata *)0xfa77)
#define     DMA_LCM_RXAH            (*(unsigned char volatile xdata *)0xfa77)
#define     DMA_LCM_RXAL            (*(unsigned char volatile xdata *)0xfa78)


/////////////////////////////////////////////////

#define     INT0_VECTOR             0       //0003H
#define     TMR0_VECTOR             1       //000BH
#define     INT1_VECTOR             2       //0013H
#define     TMR1_VECTOR             3       //001BH
#define     UART1_VECTOR            4       //0023H
#define     ADC_VECTOR              5       //002BH
#define     LVD_VECTOR              6       //0033H
#define     PCA_VECTOR              7       //003BH
#define     UART2_VECTOR            8       //0043H
#define     SPI_VECTOR              9       //004BH
#define     INT2_VECTOR             10      //0053H
#define     INT3_VECTOR             11      //005BH
#define     TMR2_VECTOR             12      //0063H
#define     USER_VECTOR             13      //006BH
#define     INT4_VECTOR             16      //0083H
#define     UART3_VECTOR            17      //008BH
#define     UART4_VECTOR            18      //0093H
#define     TMR3_VECTOR             19      //009BH
#define     TMR4_VECTOR             20      //00A3H
#define     CMP_VECTOR              21      //00ABH
#define     PWM_VECTOR              22      //00B3H
#define     PWMFD_VECTOR            23      //00BBH
#define     I2C_VECTOR              24      //00C3H
#define     P0INT_VECTOR            37      //012BH
#define     P1INT_VECTOR            38      //0133H
#define     P2INT_VECTOR            39      //013BH
#define     P3INT_VECTOR            40      //0143H
#define     P4INT_VECTOR            41      //014BH
#define     P5INT_VECTOR            42      //0153H
#define     P6INT_VECTOR            43      //015BH
#define     P7INT_VECTOR            44      //0163H
#define     M2MDMA_VECTOR           47      //017BH
#define     ADCDMA_VECTOR           48      //0183H
#define     SPIDMA_VECTOR           49      //018BH
#define     U1TXDMA_VECTOR          50      //0193H
#define     U1RXDMA_VECTOR          51      //019BH
#define     U2TXDMA_VECTOR          52      //01A3H
#define     U2RXDMA_VECTOR          53      //01ABH
#define     U3TXDMA_VECTOR          54      //01B3H
#define     U3RXDMA_VECTOR          55      //01BBH
#define     U4TXDMA_VECTOR          56      //01C3H
#define     U4RXDMA_VECTOR          57      //01CBH
#define     LCMDMA_VECTOR           58      //01D3H
#define     LCM_VECTOR              59      //01DBH

/////////////////////////////////////////////////

#endif


#ifndef MAIN_H
#define MAIN_H

typedef enum Screen {scrHome, scrMenu, scrSave, scrRevTest, scrUpload,
	scrPower, scrDensity, scrAggHard, scrAggDens, scrCustom,
scrUnits, scrLang, scrTime, scrDate, scrCal} Screen;

enum Power {pwrHigh, pwrStandard, pwrLow, pwrCustom};
enum Density {denStd, denLow, denVlow};
enum AggHardness {hardMoh3, hardMoh4, hardMoh5, hardMoh6, hardMoh7};
enum AggSize {asLow, asStd};
enum Units{Metric, Standard};
enum Language{lngEnglish, lngDeutsche, lngEspanol, lngItalien};
enum Switch{Hi, Low};

struct Settings{
	enum Power Curr_Pwr;
	enum Density Curr_Density;
	enum AggHardness Curr_Hardness;
	enum AggSize Curr_Size;
	enum Units Curr_Units;
	enum Language Curr_Lang;
}Curr_Settings;

void dsp_agg_dens( void );
void dsp_agg_hard( void );
void dsp_cal( void );
void dsp_custom( void );
void dsp_date( void );
void dsp_density(void );
void dsp_home( void );
void dsp_lang( void );
void dsp_menu( void );
void dsp_power( void );
void dsp_rev_test( void );
void dsp_save( void );
void dsp_time( void );
void dsp_units( void );
void dsp_upload( void );

bool poll_screen( void );
void poll_ad(void );

Screen spi_get_screen( void );
void spi_init_pins(void);
void spi_send_data( unsigned char *buf, unsigned char len);
//void spi_init_module(void);

/*number defines for chip*/
#define SPI_SS IOPORT_CREATE_PIN(PORTD, 2)

/*Generic #defines*/
#define FOREVER 1
#define LINE_SIZE 0x0a

#define SCR_HOME 10
#define SCR_MENU 20
#define SCR_SAVE 30
#define SCR_REVTEST 40
#define SCR_UPLOAD 50
#define SCR_POWER 60
#define SCR_DENSITY 70
#define SCR_AGGHARD 80
#define SCR_CUSTOM 90
#define SCR_UNITS 100
#define SCR_LANG 110
#define SCR_TIME 120
#define SCR_DATE 130
#define SCR_CAL 140

#endif
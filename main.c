/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <spi.h>

#include "main.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();

	/*init output pins for spi*/
	spi_init_pins();
	/*init module as master*/
//	spi_init_module();

	/* Insert application code here, after the board has been initialized. */
	enum Screen current_screen = scrHome;
	delay_s(3);
	while(FOREVER){
		switch (current_screen){
		case scrAggDens: // Aggregate density screen
			dsp_agg_dens();
			break;
		
		case scrAggHard: // Aggregate hardness screen
			dsp_agg_hard();
			break;
		
		case scrCal:  //Calibrate Screen
			dsp_cal();
			break;
		
		case scrCustom: //Custom Correllation Screen
			dsp_custom();
			break;

		case scrDate: //Adjust Date Screen
			dsp_date();
			break;

		case scrDensity: //adjust concrete density screen
			dsp_density();
			break;

		case scrHome: // Home Screen
			dsp_home();
			break;

		case scrLang: //change language
			dsp_lang();
			break;

		case scrMenu: //Maim Menu Screen
			dsp_menu();
			break;

		case scrPower: // Power Screen
			dsp_power();
			break;

		case scrRevTest:	//Review Test Screen
			dsp_rev_test();
			break;

		case scrSave: // Save Test Screen
			dsp_save();
			break;

		case scrTime:	//Change time screen
			dsp_time();
			break;

		case scrUnits:  //Change Units Screen
			dsp_units();
			break;

		case scrUpload:  //Upload Data Screen
			dsp_upload();
			break;

		default: //error?
			dsp_home();
			break;
		}
		if( poll_screen() == true ){
			current_screen = spi_get_screen();
		}
	}
}

void dsp_agg_dens( void ){

}
void dsp_agg_hard( void ){

}
void dsp_cal( void ){

//reset standard system setttings
	Curr_Settings.Curr_Density = denStd;
	Curr_Settings.Curr_Hardness = hardMoh3;
	Curr_Settings.Curr_Lang = lngEnglish;
	Curr_Settings.Curr_Pwr = pwrStandard;
	Curr_Settings.Curr_Size = asStd;
	Curr_Settings.Curr_Units = Standard;
}
void dsp_custom( void ){

}
void dsp_date( void ){

}
void dsp_density(void ){

}

void dsp_home( void ){
	poll_ad();
}

void dsp_lang( void ){

}
void dsp_menu( void ){

}
void dsp_power( void ){

}
void dsp_rev_test( void ){

}
void dsp_save( void ){

}
void dsp_time( void ){

}
void dsp_units( void ){

}
void dsp_upload( void ){

}

/*check if screen has data in output buffer*/
bool poll_screen( void ){
	bool return_value = false;

	return_value = ioport_get_pin_level(SPI_SS) == true? false : true;

	return(return_value);
}

void poll_ad(void ){

}

/*get new screen*/
Screen spi_get_screen( void ){

	unsigned char screen_number = 10;
	Screen return_screen = scrHome;

	struct spi_device spi_device_conf = {
		.id = IOPORT_CREATE_PIN(PORTD, 1)
	};
	spi_select_device(&SPID, &spi_device_conf);
	spi_read_single(&SPID, &screen_number);
	spi_deselect_device(&SPID, &spi_device_conf);

	switch (screen_number){
	case SCR_HOME:
		return_screen = scrHome;
		break;
	case SCR_MENU:
		return_screen = scrMenu;
		break;
	case SCR_SAVE:
		return_screen = scrSave;
		break;
	case SCR_REVTEST:
		return_screen = scrRevTest;
		break;
	case SCR_UPLOAD:
		return_screen = scrUpload;
		break;
	case SCR_POWER:
		return_screen = scrPower;
		break;
	case SCR_DENSITY:
		return_screen = scrDensity;
		break;
	case SCR_AGGHARD:
		return_screen = scrAggHard;
		break;
	case SCR_CUSTOM:
		return_screen = scrCustom;
		break;
	case SCR_UNITS:
		return_screen = scrUnits;
		break;
	case SCR_LANG:
		return_screen = scrLang;
		break;
	case SCR_TIME:
		return_screen = scrTime;
		break;
	case SCR_DATE:
		return_screen = scrDate;
		break;
	case SCR_CAL:
		return_screen = scrCal;
		break;
	}
	return( return_screen);
}

/*initializes pins on PORTD for SPI*/

void spi_init_pins(void)
{
/* init pins for spi comm */
	ioport_configure_port_pin(&PORTD, PIN1_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);//cs
	ioport_configure_port_pin(&PORTD, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT); //ss
	ioport_configure_port_pin(&PORTD, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);//MOSI
	ioport_configure_port_pin(&PORTD, PIN6_bm, IOPORT_DIR_INPUT);//MISO
	ioport_configure_port_pin(&PORTD, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);//SCL

/*init and enable SPI */
	struct spi_device spi_device_conf = {
		.id = IOPORT_CREATE_PIN(PORTD, 1)
	};
	spi_master_init(&SPID);
	spi_master_setup_device(&SPID, &spi_device_conf, SPI_MODE_0, 200000, 0);//SPI Mode 0 - pull pins 14 & 15 LO on Display 200KHz delay after write
	spi_enable(&SPID);

/* init pins for ready for input signal */
	ioport_init();
	ioport_set_pin_dir(SPI_SS, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(SPI_SS, IOPORT_MODE_PULLUP);
}

void spi_send_data( unsigned char *buf, unsigned char len){


}

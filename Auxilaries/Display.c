/*
 * Display.c
 *
 *  Created on: Oct 9, 2024
 *      Author: pc
 */
//#include"usart.h"
#include"sharedData.h"
#include"define.h"
#include<string.h>

//static uint8_t validAddress[3] = { 0x01, 0x14, 0x01 };
//static uint8_t frontendAddress[2] = { 68, 70 };
// code for transmission starts here
DISPLAY_VAL_t Display;

void transmit(uint8_t* tx_data) {
//	static uint8_t tx_data[14] = { 0x02, 0x0E, 0x01, 0x00, 0x00, 0x00, 0x00,
//			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t crc = 0;
	uint16_t speed = Measured.singleWireSpeed.tickDiff;
//	uint16_t speed = 1000/(measured.motorSpeed.speed/4.5);
	Display.out.current = Measured.Current.calculated / 100;
	tx_data[3] = Display.out.errorCode8.code;
	tx_data[4] = Display.out.brake;
	tx_data[6] = Display.out.current;
	tx_data[8] = (uint8_t) (speed >> 8 & 0xFF);
	tx_data[9] = (uint8_t) (speed & 0xFF);

	for (int i = 0; i < 13; i++) {
		crc ^= tx_data[i];
	}
	tx_data[13] = crc;

//	HAL_UART_Transmit_IT(&huart1, tx_data, 14);
}


void display_handleTransmission(uint8_t* tx_data) {
	transmit(tx_data);
}

//extern void get_tx_data(uint8_t* buffer);


// Code for transmission ends here

// Code for reception starts here

//void acceptDataIfAddressMatch() {
//	if (Communication.rxBuf[0] == validAddress[0]
//			&& Communication.rxBuf[1] == validAddress[1]
//			&& Communication.rxBuf[2] == validAddress[2]) {
//		memcpy(Communication.rawData, Communication.rxBuf, DISPLAY_RX_SIZE);
////		display_parse();
//		Communication.source = 0;
//	}
//}
//void acceptFrontendAdress() {
//	if (Communication.rxBuf[0] == frontendAddress[0]
//			&& Communication.rxBuf[1] == frontendAddress[1]) {
//		memcpy(Communication.rawData, Communication.rxBuf, DISPLAY_RXBUF_SIZE);
////		frontend_parse();
//		Communication.source = 1;
//	}
//}
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	if (huart->Instance == USART1) {
//		acceptDataIfAddressMatch();
////		acceptFrontendAdress();
//		HAL_UART_Receive_IT(&huart1, Communication.rxBuf, DISPLAY_RX_SIZE);
//		Display.lastReceptionTime = HAL_GetTick();
//	}
//}
//
//void display_handleReception() {
//	if (HAL_GetTick() > Display.lastReceptionTime + DISPLAY_RECONNECT_TIMEOUT) {
//		if (HAL_GetTick() > Display.lastReconnectionAttempt + 100) {
//			HAL_UART_AbortReceive_IT(&huart1);
//			HAL_UART_Receive_IT(&huart1, Communication.rxBuf, DISPLAY_RX_SIZE);
//			Display.lastReconnectionAttempt = HAL_GetTick();
//		}
//	}
//}


#pragma once

enum class SignalType {
	BUY, 
	SELL, 
	HOLD
};

struct Signal {
	SignalType type{ SignalType::HOLD};
	int quantity{ 0 };
};
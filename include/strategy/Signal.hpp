#pragma once

enum class SignalType {
	Buy, 
	Sell, 
	Hold
};

struct Signal {
	SignalType type{ SignalType:Hold };
	int quantity{ 0 };
};
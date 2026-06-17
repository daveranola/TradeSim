class Strategy {
public:
	virtual ~Strategy() = default;
	virtual Signal onBar(const Bar& bar) = 0;
};
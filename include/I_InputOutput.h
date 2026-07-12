class IPinCommand
{
public:
    virtual ~IPinCommand() = default;

    virtual void configureInputDitigal(std::uint8_t pin) = 0;
    virtual void configureOutputDigital(std::uint8_t pin) = 0;
    virtual int readDigital(std::uint8_t pin) = 0;
    virtual int writeDigital(std::uint8_t pin) = 0;

    virtual void configureInputAnalog(std::uint8_t pin) = 0;
    virtual void configureOutputAnalog(std::uint8_t pin) = 0;
    virtual int readAnalog(std::uint8_t pin) = 0;
    virtual int writeAnalog(std::uint8_t pin) = 0;
};
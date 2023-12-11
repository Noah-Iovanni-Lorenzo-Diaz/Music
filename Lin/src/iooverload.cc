std::istream& operator>> (std::istream& in, Options& option) {
    int input{};
    in >> input; // input an integer

    option = static_cast<Options>(input);
    return in;
}

std::ostream& operator<<(std::ostream& out, Options option)
{
	switch (option)
	{
	case PLAY:  return out << "PLAY";
	case PAUSE: return out << "PAUSE";
	case STOP:  return out << "STOP";
    case EXIT:  return out << "EXIT";
	default:    return out << "???";
	}
}
class Message {
public:
    Message() : text_{}, id_{-1} {}

    Message(const string& text, const int id) : text_(text), id_{id} {}

    const string& get_text() const noexcept {
        return text_;
    }

    int get_id() const noexcept {
        return id_;
    }

private:
    string text_;
    int id_;
};

inline bool operator<(const Message& lhs, const Message& rhs) noexcept {
    return lhs.get_id() < rhs.get_id();
}

inline bool operator>(const Message& lhs, const Message& rhs) noexcept {
    return rhs < lhs;
}

class MessageFactory {
public:
    MessageFactory() : message_count_{0} {}

    Message create_message(const string& text) {
        return Message{text, message_count_++};
    }

private:
    int message_count_;
};

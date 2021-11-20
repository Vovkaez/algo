class dl_list {
public:
    dl_list_node* head;
    int size = 0;
    dl_list() {
        head = new dl_list_node(-1);
        head->set_next(head);
        head->set_prev(head);
    }

    ~dl_list() {
        while (head->get_next() != head) {
            auto node = head->get_next();
            node->erase();
        }
        delete head;
    }

    void add_after(dl_list_node* node, int value) {
        ++size;
        auto* cur_node = new dl_list_node(value);
        auto* next_node = node->get_next();
        node->set_next(cur_node);
        cur_node->set_prev(node);
        cur_node->set_next(next_node);
        next_node->set_prev(cur_node);
    }

    void push_back(int value) {
        add_after(head->get_prev(), value);
    }

    friend ostream& operator<<(ostream& s, dl_list& list) {
        for (dl_list_node* current = list.head->get_next(); current != list.head; current = current->get_next()) {
            s << current->get_value() << ' ';
        }
        return s;
    }
};

class dl_list_node {
private:
    dl_list_node* next;
    dl_list_node* prev;
    int value;
public:
    explicit dl_list_node(int _value) : value(_value) {
        next = prev = nullptr;
    };

    dl_list_node() : dl_list_node(0) {}

    void erase() {
        auto* prev_node = prev;
        auto* next_node = next;
        prev_node->set_next(next_node);
        next_node->set_prev(prev_node);
        delete this;
    }

    bool has_next() {
        return next;
    }

    bool has_prev() {
        return prev;
    }

    dl_list_node* get_next() {
        return next;
    }

    dl_list_node* get_prev() {
        return prev;
    }

    void set_next(dl_list_node* _next) {
        next = _next;
    }

    void set_prev(dl_list_node* _prev) {
        prev = _prev;
    }

    int get_value() {
        return value;
    }
};

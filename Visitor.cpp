/*
 * Паттерн Пометитиель
 *
 * Назначение: позволяет задавать новые операции над объектами без
 * модификации этих классов этих объектов.
 */

#include <string>
#include <iostream>

class Visitor;
class Row;
class Symbol;

class Glyph {
public:
    ~Glyph() = default;
    virtual std::string get_glyph_info() const = 0;
    virtual void accept(Visitor& visitor) = 0;
};

class Visitor {
public:
    virtual void visit(Row& row) = 0;
    virtual void visit(Symbol& symbol) = 0;
};

// Components
class Symbol : public Glyph {
public:
    Symbol(char symbol = 'a')
        : symbol(symbol) {}

    std::string get_glyph_info() const override {
        return {symbol};
    }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    char symbol;
};

class Row : public Glyph {
public:
    Row(int row_number, int elements_in_row)
        : _row_number(row_number), _elements_in_row(elements_in_row) {}

    std::string get_glyph_info() const override {
        return "Row " + std::to_string(_row_number) + " with " + std::to_string(_elements_in_row) + " elements";
    }

    int get_row_number() const { return _row_number; }
    int get_elements_in_row() const { return _elements_in_row; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    int _row_number;
    int _elements_in_row;
};

// Visitors
class SimpleVisitor : public Visitor {
public:
    void visit(Row& row) override {
        std::cout << "Simple visitor" << '\n';
        std::cout << row.get_glyph_info() << '\n';
    }

    void visit(Symbol& symbol) override {
        std::cout << "Simple visitor" << '\n';
        std::cout << symbol.get_glyph_info() << '\n';
    }
};

class AdvancedVisitor : public Visitor {
public:
    void visit(Row& row) override {
        std::cout << "Advanced visitor" << '\n';
        std::cout << "Row number: " << row.get_row_number() << '\n';
        std::cout << "Number of elements in row: " << row.get_elements_in_row() << '\n';
        std::cout << "Row * Number of elements = " << row.get_elements_in_row() * row.get_row_number() << '\n';
    }

    void visit(Symbol& symbol) override {
        std::cout << "Advanced visitor" << '\n';
        std::cout << symbol.get_glyph_info() << '\n';
    }
};

int main() {
    Row row1(2, 3);
    Row row2(3, 13);

    SimpleVisitor simple_visitor{};
    AdvancedVisitor advanced_visitor{};

    row1.accept(simple_visitor);
    std::cout << '\n';
    row1.accept(advanced_visitor);
    std::cout << '\n';
    row2.accept(advanced_visitor);
}

/*
OUTPUT:

Simple visitor
Row 2 with 3 elements

Advanced visitor
Row number: 2
Number of elements in row: 3
Row * Number of elements = 6

Advanced visitor
Row number: 3
Number of elements in row: 13
Row * Number of elements = 39
 */
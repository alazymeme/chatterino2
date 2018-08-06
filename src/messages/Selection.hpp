#pragma once

#include <utility>

namespace chatterino {

struct SelectionItem {
    int messageIndex;
    int charIndex;

    SelectionItem()
    {
        this->messageIndex = 0;
        this->charIndex = 0;
    }

    SelectionItem(int _messageIndex, int _charIndex)
    {
        this->messageIndex = _messageIndex;

        this->charIndex = _charIndex;
    }

    bool operator<(const SelectionItem &b) const
    {
        if (this->messageIndex < b.messageIndex) {
            return true;
        }
        if (this->messageIndex == b.messageIndex &&
            this->charIndex < b.charIndex) {
            return true;
        }
        return false;
    }

    bool operator>(const SelectionItem &b) const
    {
        return b.operator<(*this);
    }

    bool operator==(const SelectionItem &b) const
    {
        return this->messageIndex == b.messageIndex &&
               this->charIndex == b.charIndex;
    }

    bool operator!=(const SelectionItem &b) const
    {
        return this->operator==(b);
    }
};

struct Selection {
    SelectionItem start;
    SelectionItem end;
    SelectionItem selectionMin;
    SelectionItem selectionMax;

    Selection() = default;

    Selection(const SelectionItem &start, const SelectionItem &end)
        : start(start)
        , end(end)
        , selectionMin(start)
        , selectionMax(end)
    {
        if (selectionMin > selectionMax) {
            std::swap(this->selectionMin, this->selectionMax);
        }
    }

    bool isEmpty() const
    {
        return this->start == this->end;
    }

    bool isSingleMessage() const
    {
        return this->selectionMin.messageIndex ==
               this->selectionMax.messageIndex;
    }
};

}  // namespace chatterino

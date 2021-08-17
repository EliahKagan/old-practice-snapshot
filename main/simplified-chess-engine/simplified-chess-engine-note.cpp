        // move southwest
        for (auto ii = i, jj = j, d = std::min(i, j); d != 0u; --d) {
            if (board_[--ii][--jj] == Object::empty) {
                if (try_move(i, j, ii, jj)) return true;
            } else {
                if (!belongs_to(player_, board_[ii][jj])
                            && try_move(i, j, ii, jj))
                    return true;

                break; // can't move past even a capturable piece
            }
        }
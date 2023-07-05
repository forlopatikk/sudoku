#include "sudoku.h"
#include "sdkwindow.h"

Sudoku::Sudoku(QWidget* parent) :
    QWidget(parent),
    _check {new QPushButton("Check",this)},
    _solve {new QPushButton("Get Solve",this)},
    _return{new QPushButton("Return to Menu",this)},
    _help{new QPushButton("Help",this)},
    _timer{new QTimer(this)},
    _seconds{0},
    _timer_lbl{new QLabel("0 second later",this)}
{
    QGridLayout* main_layout = new QGridLayout(this);
    for (int i = 0; i < 9; i+=1)
    {
        for (int j = 0; j < 9; j+=1)
        {
            _cells[i][j] = new CellBtn(this);
            _cells[i][j]->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
            main_layout->addWidget(_cells[i][j],i + i/3,j + j/3);
        }
    }
    main_layout->addItem(new QSpacerItem(30,30),3,3);
    main_layout->addItem(new QSpacerItem(30,30),7,7);
    main_layout->addItem(new QSpacerItem(0,30),13,0);
    connect(_solve ,&QPushButton::clicked,this,&Sudoku::Solve);
    connect(_check ,&QPushButton::clicked,this,&Sudoku::Check);
    connect(_return,&QPushButton::clicked,this,&Sudoku::ClickedReturnBtn);
    connect(_help,&QPushButton::clicked,this,&Sudoku::Help);
    main_layout->addWidget(_solve ,14,0,1,3);
    main_layout->addWidget(_help ,14,4,1,3);
    main_layout->addWidget(_return,14,8,1,3);
    main_layout->addWidget(_check ,15,8,1,3);
    main_layout->addWidget(_timer_lbl,15,0,1,7);


    _check->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);

    _timer_lbl->setAlignment(Qt::Alignment::enum_type::AlignCenter);

    _timer->setTimerType(Qt::TimerType::VeryCoarseTimer);
    connect(_timer,&QTimer::timeout,this,&Sudoku::Update);

    this->setLayout(main_layout);
    setWindowTitle("Sudoku");
}

bool Sudoku::IsSandboxMode() // режим пісочниці.
{
    return _sandbox_mode;
}

void Sudoku::Generate(int open_slots_count)
{
    Cell sdk[9][9];

    for (int row = 0; row < 9; )
    {
        for (int column = 0; column < 9; )
        {
            for (int tmp_column = 0; tmp_column < column; tmp_column += 1)
            {
                sdk[row][column].RemoveFD(sdk[row][tmp_column].GetDigit());
            }
            for (int tmp_row = 0; tmp_row < row; tmp_row += 1)
            {
                sdk[row][column].RemoveFD(sdk[tmp_row][column].GetDigit());
            }

            {
                int tmp_row = row / 3 * 3;
                int tmp_column = column / 3 * 3;

                while (not ((tmp_row == row) && (tmp_column == column)))
                {
                    sdk[row][column].RemoveFD(sdk[tmp_row][tmp_column].GetDigit());
                    tmp_column += 1;
                    if (tmp_column >= column / 3 * 3 + 3)
                    {
                        tmp_row += 1;
                        tmp_column = column / 3 * 3;
                    }
                }
            }


            if (not sdk[row][column].GenerateDigit())
            {
                if ((row == 0) and (column == 0)) exit(-1);
                sdk[row][column].Reset();
                if (column == 0)
                {
                    row -= 1;
                    column = 8;
                }
                else column -= 1;

                continue;
            }
            column += 1;
        }
        row += 1;
    }

    static bool opened[9 * 9];
    for (int i = 0; i < 9 * 9; i += 1)
    {
        opened[i] = false;
    }

    for (int i = 0; i < open_slots_count; i += 1)
    {
        int tmp = rand() % (9 * 9 - i);
        int true_num = 0;
        while (true)
        {
            if (not opened[true_num])
            {
                if (tmp == 0)
                {
                    break;
                }
                tmp -= 1;
            }
            true_num += 1;
        }
        opened[true_num] = true;
    }
    for (int row = 0; row < 9; row += 1)
    {
        for (int column = 0; column < 9; column += 1)
        {

            bool t = true;
            for (int i = 0; i < open_slots_count; i += 1)
            {
                if (opened[column + (row * 9)])
                {
                    _cells[row][column]->SetDigit(sdk[row][column].GetDigit());
                    _cells[row][column]->Lock();
                    t = false;
                    break;
                }
            }
            if (t)
            {
                _cells[row][column]->SetDigit(0);
                _cells[row][column]->Open();
            }
        }
    }

    _sandbox_mode = not open_slots_count;
    _open_slots_count = open_slots_count;

    if (_sandbox_mode)
    {
        _timer_lbl->setText("SANDBOX MODE. Use right-click");
    }
    else
    {
        _seconds = 0;
        _timer_lbl->setText("0 seconds later");
        _timer->start(1000);
    }
}

void Sudoku::PlayTxtGame()
{
    _sandbox_mode = true;
    _timer_lbl->setText("Load mode. Use right-click");

    QFile file("mysdk.txt");
    if (not file.open(QIODevice::ReadOnly)) exit(-1);
    QTextStream out(&file);
    QString tmp;
    std::pair<int,int> current {0,0};
    while(not out.atEnd())
    {
        out >> tmp;
        if ((tmp != QString("|")) and (tmp != QString("—————————————————————")))
        {
            // qDebug() << tmp;
            _cells[current.first][current.second]->SetDigit(tmp.toInt());
            current.second += 1;
            if (current.second == 9)
            {
                current.second = 0;
                current.first += 1;
            }
        }
    }
}

void Sudoku::Solve() // autosolve
{
    _solve->setText("u cheater");

    bool columns [9][9];
    bool rows [9][9];;
    bool squares [9][9];
    for (int i = 0; i < 9; i+=1)
    {
        for (int j = 0; j < 9; j += 1)
        {
            columns[i][j] = true;
            rows[i][j] = true;
            squares[i][j] = true;
        }
    }

    for (int column = 0; column < 9; column += 1)
    {
        for (int row = 0; row < 9; row += 1)
        {
            if (not _cells[row][column]->IsLocked())
            {
                continue;
            }

            if (_cells[row][column]->GetDigit() == 0)
            {
                _timer_lbl->setText("there are no solutions");
                _timer_lbl->setStyleSheet("color: red;");
                return;
            }

            if ((columns[column][_cells[row][column]->GetDigit()-1]) and (rows[row][_cells[row][column]->GetDigit()-1])
                and (squares[row / 3 + column / 3 * 3][_cells[row][column]->GetDigit() - 1]))
            {
                columns[column][_cells[row][column]->GetDigit() - 1] = false;
                rows[row][_cells[row][column]->GetDigit() - 1] = false;
                squares[row / 3 + column / 3 * 3][_cells[row][column]->GetDigit() - 1] = false;
            }
            else
            {
                _timer_lbl->setText("there are no solutions");
                _timer_lbl->setStyleSheet("color: red;");
                return;
            }
        }
    }

    Cell sdk[9][9];

    for (int row = 0; row < 9; )
    {
        for (int column = 0; column < 9; )
        {
            if (_cells[row][column]->IsLocked())
            {
                sdk[row][column].SetDigit(_cells[row][column]->GetDigit());
                column += 1;
                continue;
            }
            for (int tmp_column = 0; tmp_column < column; tmp_column += 1)
            {
                sdk[row][column].RemoveFD(sdk[row][tmp_column].GetDigit());
            }
            for (int tmp_row = 0; tmp_row < row; tmp_row += 1)
            {
                sdk[row][column].RemoveFD(sdk[tmp_row][column].GetDigit());
            }
            for (int tmp_column = column+1; tmp_column < 9; tmp_column += 1)
            {
                if (_cells[row][tmp_column]->IsLocked())
                {
                    sdk[row][column].RemoveFD(_cells[row][tmp_column]->GetDigit());
                }
            }
            for (int tmp_row = row+1; tmp_row < 9; tmp_row += 1)
            {
                if (_cells[tmp_row][column]->IsLocked())
                {
                    sdk[row][column].RemoveFD(_cells[tmp_row][column]->GetDigit());
                }
            }

            {
                int tmp_row = row / 3 * 3;
                int tmp_column = column / 3 * 3;
                while (not ((tmp_row == row) and (tmp_column == column)))
                {
                    sdk[row][column].RemoveFD(sdk[tmp_row][tmp_column].GetDigit());
                    tmp_column += 1;
                    if (tmp_column >= column / 3 * 3 + 3)
                    {
                        tmp_row += 1;
                        tmp_column = column / 3 * 3;
                    }
                }
            }

            {
                int tmp_row = row / 3 * 3 + 2;
                int tmp_column = column / 3 * 3 + 2;
                while (not ((tmp_row == row) and (tmp_column == column)))
                {
                    if (_cells[tmp_row][tmp_column]->IsLocked())
                    {
                        sdk[row][column].RemoveFD(sdk[tmp_row][tmp_column].GetDigit());
                    }
                    tmp_column -= 1;
                    if (tmp_column < column / 3 * 3)
                    {
                        tmp_row -= 1;
                        tmp_column = column / 3 * 3 + 2;
                    }
                }
            }

            if (not sdk[row][column].GenerateDigit())
            {
                sdk[row][column].Reset();

                if (column == 0)
                {
                    row -= 1;
                    column = 9 -1;
                }
                else column -= 1;

                if (row<0)
                {
                    _timer_lbl->setText("there are no solutions");
                    _timer_lbl->setStyleSheet("color: red;");
                    return;
                }

                while (_cells[row][column]->IsLocked())
                {

                    if (column == 0)
                    {
                        row -= 1;
                        column = 9 - 1;
                    }
                    else column -= 1;

                    if (row<0)
                    {
                        _timer_lbl->setText("there are no solutions");
                        _timer_lbl->setStyleSheet("color: red;");
                        return;
                    }
                }

                continue;
            }
            column += 1;
        }
        row += 1;
    }

    for (int row = 0; row < 9; row += 1)
    {
        for (int column = 0; column < 9; column += 1)
        {
            _cells[row][column]->SetDigit(sdk[row][column].GetDigit());
        }
    }
}

void Sudoku::Help() // підсказка
{
    auto err = FindError();
    if (err == std::make_pair<int,int>(-1,-1))
    {
        _check->setStyleSheet("background-color: green;");
    }
    else
    {
        _cells[err.first][err.second]->setStyleSheet(_cells[err.first][err.second]->styleSheet() + ";border: 2px solid rgb(0,200,250);");
    }
}

void Sudoku::ClickedReturnBtn() //  відправляє сигнал про повернення до головного меню
{
    emit ReturnToMenu();
}

void Sudoku::Check() // перевірка на помилки в грі + запис у файл.
{
    if (FindError() == std::make_pair<int,int>(-1,-1)) {
        _check->setStyleSheet("background-color: green;");
        if (not _sandbox_mode)
        {
            _timer->stop();
            QFile file("base.txt");
            QString result = "Won in " + QString::number(_seconds) + " seconds Sudoku with "
                             + QString::number(_open_slots_count) +  " closen cells";
            if (file.open(QIODevice::Append)) {
                QTextStream out(&file);
                out << Qt::endl;
                out << result << Qt::endl;
                out << "Sudoku Matrix:" << Qt::endl;
                for (int row = 0; row < 9; row++) {
                    for (int column = 0; column < 9; column++) {
                        out << _cells[row][column]->GetDigit();
                        if (column % 3 == 2 && column != 8)
                            out << " | ";
                        else if (column != 8)
                            out << " ";
                    }
                    out << Qt::endl;
                    if (row % 3 == 2 && row != 8)
                        out << "—————————————————————" << Qt::endl;
                }
            }
            file.close();
            _sandbox_mode = true;
        }
    }
    else _check->setStyleSheet("background-color: red;");
}

void Sudoku::Update() // апдейт таймеру
{
    _seconds += 1;
    _timer_lbl->setText(QString::number(_seconds) + " second later");
    if (_check->styleSheet() == "background-color: red;") _check->setStyleSheet("");
}

std::pair<int, int> Sudoku::FindError()
{
    static bool columns [9][9];
    static bool rows [9][9];
    static bool squares [9][9];
    for (int i = 0; i < 9; i+=1)
    {
        for (int j = 0; j < 9; j += 1)
        {
            columns[i][j] = true;
            rows[i][j] = true;
            squares[i][j] = true;
        }
    }

    for (int column = 0; column < 9; column += 1) // перевірка наявності помилки в Sudoku.
    {
        for (int row = 0; row < 9; row += 1)
        {
            if (_cells[row][column]->GetDigit() == 0)
            {
                return {row, column};
            }

            if ((columns[column][_cells[row][column]->GetDigit()-1]) and (rows[row][_cells[row][column]->GetDigit()-1])
                and (squares[row / 3 + column / 3 * 3][_cells[row][column]->GetDigit() - 1]))
            {
                columns[column][_cells[row][column]->GetDigit() - 1] = false;
                rows[row][_cells[row][column]->GetDigit() - 1] = false;
                squares[row / 3 + column / 3 * 3][_cells[row][column]->GetDigit() - 1] = false;
            }
            else
            {
                return {row, column};
            }
        }
    }

    return {-1,-1};
}

void Sudoku::resizeEvent(QResizeEvent* event)  // зміна розміру вікна sudoku
{
    QWidget::resizeEvent(event);
    QFont tmp;
    tmp.setPixelSize(_timer_lbl->height()/2);
    _timer_lbl->setFont(tmp);
}

void Sudoku::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event); // малювання таблиці Sudoku на вікні
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap));
    painter.setRenderHint(QPainter::Antialiasing);
    int sdk_table_height = (height()-_return->height()-_check->height()-30);
    painter.drawLine(0,sdk_table_height/3,width(),sdk_table_height/3);    // малювання горизонтальних ліній таблиці Sudoku
    painter.drawLine(0,sdk_table_height/3*2,width(),sdk_table_height/3*2);
    painter.drawLine(0,sdk_table_height,width(),sdk_table_height);
    painter.drawLine(width()/3,0,width()/3,sdk_table_height); // малювання вертикальних ліній таблиці Sudoku
    painter.drawLine(width()/3*2,0,width()/3*2,sdk_table_height);
}



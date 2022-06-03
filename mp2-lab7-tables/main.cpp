#include <iostream>
#include <clocale>
#include <cmath>
#include <cstdlib>
#include <random>
#include "TSortTable.h"
#include "TArrayHash.h"
#include "TTreeTable.h"
#include "TBalancedTree.h"

using namespace std;

TTable* pTable;

void fill_table(TTable* table, int entriesCount, int keyMax)
{
	for (int i = 0; i < entriesCount; i++)
	{
		TKey randKey = (int)((double)rand() / (RAND_MAX + 1) * (keyMax + 1));

		bool inserted = table->Insert(
			TRecord(randKey, "value" + to_string(randKey))
		);
		if (!inserted) i--;
	}
}

void show_table(TTable* table)
{
	if (typeid(*table) == typeid(TTreeTable)
		|| typeid(*table) == typeid(TBalancedTree))
	{
		if (!(*pTable).IsEmpty())
		{
			((TTreeTable*)table)->Print(cout);
			cout << "\n";
		}
		else
			cout << "Пуста.\n\n";
	}
	else
	{
		if (!(*pTable).IsEmpty())
			cout << (*pTable) << "\n";
		else
			cout << "Пуста.\n\n";
	}
}

int main()
{
	setlocale(LC_ALL, "russian");

	while (true)
	{
		cout << "Доступные типы таблиц:\n";
		cout << "1  -  Просматриваемая (TScanTable);\n";
		cout << "2  -  Отсортированная (TSortTable);\n";
		cout << "3  -  Отсортированная (TSortTable) через TScanTable + QuickSort; \n";
		cout << "4  -  Отсортированная (TSortTable) через TScanTable + SelectionSort; \n";
		cout << "5  -  Хэш-таблица на массиве (TArrayHash);\n";
		cout << "6  -  Таблица на дереве (TTreeTable);\n";
		cout << "7  -  Таблица на сбалансированном дереве (TBalancedTree);\n";


		int tableType;
		cout << "Тип таблицы: ";
		cin >> tableType;

		int tableSize = -1;

		if (tableType != 6 && tableType != 7)
		{
			cout << "Размер таблицы: ";
			cin >> tableSize;
		}

		int entriesCount;
		cout << "Число случайных записей: ";
		cin >> entriesCount;

		int keyMax;
		cout << "Возможный максимальный ключ: ";
		cin >> keyMax;

		switch (tableType)
		{
		case 1:
		{
			pTable = new TScanTable(tableSize);
			fill_table(pTable, entriesCount, keyMax);
			break;
		}
		case 2:
		{
			pTable = new TSortTable(tableSize);
			fill_table(pTable, entriesCount, keyMax);
			break;
		}
		case 3:
		{
			TScanTable* temp1 = new TScanTable(tableSize);
			fill_table(temp1, entriesCount, keyMax);

			cout << "\nВременно создана таблица: \n";
			cout << (*temp1) << "\n\n";

			sortmode = false;
			pTable = new TSortTable(*temp1);
			delete temp1;
			break;
		}
		case 4:
		{
			TScanTable* temp2 = new TScanTable(tableSize);
			fill_table(temp2, entriesCount, keyMax);

			cout << "\nВременно создана таблица: \n";
			cout << (*temp2) << "\n\n";

			sortmode = true;
			pTable = new TSortTable(*temp2);
			delete temp2;
			break;
		}
		case 5:
		{
			int step;
			cout << "Шаг хэширования: ";
			cin >> step;

			pTable = new TArrayHash(tableSize, step);
			fill_table(pTable, entriesCount, keyMax);
			break;
		}
		case 6:
		{
			pTable = new TTreeTable();
			fill_table(pTable, entriesCount, keyMax);
			break;
		}
		case 7:
		{
			pTable = new TBalancedTree();
			fill_table(pTable, entriesCount, keyMax);
			break;
		}
		}

		cout << "Таблица сгенерирована.\n";
		cout << "Эффективность генерации: "
			<< pTable->GetEff() << "\n\n";
		show_table(pTable);

		pTable->ClearEff();

		while (true)
		{
			TKey key;
			cout << "Ключ (или -1 для смены таблицы): ";
			cin >> key;
			cout << '\n';
			if (key == -1) break;

			cout << "Поиск (1), добавление (2) или удаление (3): ";
			int op;
			cin >> op;

			if (op == 1)
			{
				bool result = pTable->Find(key);



				if (result)
					cout << "Удалось найти элемент " << key << ". "
					<< "Эффективность: " << pTable->GetEff()
					<< "\n\n";
				else
					cout << "Не удалось найти элемент " << key << ". "
					<< "Эффективность: " << pTable->GetEff()
					<< "\n\n";
				pTable->ClearEff();
			}
			else if (op == 2)
			{
				bool result = false;

				try
				{
					result = pTable->Insert(
						TRecord(key, "value" + to_string(key)));

					if (result)
					{
						cout << "Добавление успешно завершено. "
							<< "Эффективность: "
							<< pTable->GetEff() << "\n\n";
						cout << "Таблица теперь:\n";
						show_table(pTable);
					}
					else
						cout << "Элемент с таким ключом уже есть в "
						<< "таблице. Эффективность: "
						<< pTable->GetEff() << "\n\n";
				}
				catch (...)
				{
					cout << "Не удалось добавить элемент: "
						<< "таблица переполнена.\n\n";
				}

				pTable->ClearEff();
			}
			else if (op == 3)
			{
				bool result = pTable->Delete(key);

				if (result)
				{
					cout << "Элемент успешно найден и удалён. "
						<< "Эффективность: "
						<< pTable->GetEff() << "\n\n";
					cout << "Таблица теперь:\n";
					show_table(pTable);
				}
				else
					cout << "Элемент с таким ключом не найден. "
					<< "Эффективность: "
					<< pTable->GetEff() << '\n';

				pTable->ClearEff();
			}
		}
	}
}

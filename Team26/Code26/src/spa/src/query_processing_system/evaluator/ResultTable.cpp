#include "ResultTable.h"
#include <algorithm>
#include "Util.h"

ResultTable::ResultTable() = default;

ResultTable::ResultTable(TableRow columnNames) {
    for (int i = 0; i < columnNames.size(); i++) {
        columnNameMap.insert({i, columnNames.at(i)});
    }
}

ResultTable::ResultTable(std::string columnName) {
    columnNameMap.insert({0, columnName});
}

std::shared_ptr<ResultTable>
ResultTable::createSingleColumnTable(std::string column1, std::unordered_set<std::string> values) {
    auto res = std::make_shared<ResultTable>(column1);
    for (auto i : values) {
        res->insertRow({i});
    }
    return res;
}

std::shared_ptr<ResultTable>
ResultTable::createTableFromMap(std::unordered_map<std::string, std::unordered_set<std::string>> map,
                                std::string keysCol, std::string valuesCol) {
    if (keysCol == valuesCol) {
        return createSingleColumnTable(keysCol, Util::getAllKeys(map));
    }

    auto colNames = TableRow {keysCol, valuesCol};
    auto res = std::make_shared<ResultTable>(colNames);
    for (auto const& [k, v] : map) {
        for (auto item : v) {
            res->insertRow({k, item});
        }
    }
    return res;
}

std::shared_ptr<ResultTable>
ResultTable::joinTable(std::shared_ptr<ResultTable> table1, std::shared_ptr<ResultTable> table2) {
    auto commonCols = table1->hasMatchingColumns(table2->getColumnsNamesSet());
    if (commonCols.empty()) {
        return joinNoCommonColumns(table1, table2);
    } else {
        return joinOnColumns(table1, table2, commonCols);
    }
}

std::shared_ptr<ResultTable>
ResultTable::joinNoCommonColumns(std::shared_ptr<ResultTable> table1, std::shared_ptr<ResultTable> table2) {
    auto newTableColumns = ResultTable::getVectorUnion(table1->getColumnsNames(), table2->getColumnsNames());
    auto res = std::make_shared<ResultTable>(newTableColumns);
    for (int i = 0; i < table1->getNumberOfRows(); i++) {
        for (int j = 0; j < table2->getNumberOfRows(); j++) {
            TableRow row;
            auto table1Row = table1->getRow(i);
            auto table2Row = table2->getRow(j);
            row.insert(row.end(), table1Row.begin(), table1Row.end());
            row.insert(row.end(), table2Row.begin(), table2Row.end());
            res->insertRow(row);
        }
    }
    return res;
}

std::shared_ptr<ResultTable> ResultTable::joinOnColumns(std::shared_ptr<ResultTable> table1,
                                                       std::shared_ptr<ResultTable> table2,
                                                       std::vector<std::string> &commonColumns) {
    auto col1 = table1->getColumnNumbers(commonColumns);
    auto col2 = table2->getColumnNumbers(commonColumns);
    if (!col1.empty() && !col2.empty()) {
        if (table1->getNumberOfRows() > table2->getNumberOfRows()) {
            return joinOnColumns(table1, table2, col1, col2);
        } else {
            return joinOnColumns(table2, table1, col2, col1);
        }
    } else {
        throw std::exception();
    }
}

std::shared_ptr<ResultTable> ResultTable::joinOnColumns(std::shared_ptr<ResultTable> table1,
                                                       std::shared_ptr<ResultTable> table2,
                                                       std::vector<int> &column1,
                                                       std::vector<int> &column2) {
    auto newTableColumns = ResultTable::getVectorUnion(table1->getColumnsNames(), table2->getColumnsNames());
    auto res = std::make_shared<ResultTable>(newTableColumns);
    if (table2->getNumberOfRows() == 0 || table1->getNumberOfRows() == 0) {
        // Joining with an empty table
        return res;
    }

    std::unordered_multimap<std::vector<std::string >, int, VectorHash> hashmap;
    for (int i = 0; i < table2->getNumberOfRows(); i++) {
        hashmap.insert({table2->getValuesAt(i, column2), i});
    }

    for (int i = 0; i < table1->getNumberOfRows(); i++) {
        auto range = hashmap.equal_range(table1->getValuesAt(i, column1));
        for (auto it = range.first; it != range.second; it++) {
            TableRow row = joinTableHelper(table1->getRow(i), table2->getRow(it->second), column2);
            res->insertRow(row);
        }
    }
    return res;
}

TableRow ResultTable::joinTableHelper(TableRow table1Row, TableRow table2Row, std::vector<int> &column2) {
    TableRow row;
    row.insert(row.end(), table1Row.begin(), table1Row.end());
    for (int j = 0; j < table2Row.size(); j++) {
        if (std::find(column2.begin(), column2.end(), j) == column2.end()) {
            row.push_back(table2Row.at(j));
        }
    }
    return row;
}

int ResultTable::getColumnNumber(const std::string& colName) const {
    for (auto const& [k, v] : columnNameMap) {
        if (colName == v) {
            return k;
        }
    }
    return -1;
}
std::vector<int> ResultTable::getColumnNumbers(std::vector<std::string> &colName) const {
    std::vector<int> res(colName.size());
    for (auto const& [k, v] : columnNameMap) {
        auto it = colName.begin();
        auto col = v;
        while ((it = std::find_if(it, colName.end(), [col](std::string x) { return x == col; })) != colName.end()) {
            res.at(it - colName.begin()) = k;
            it++;
        }
    }
    return res;
}

void ResultTable::insertRow(TableRow row) {
    if (row.size() != columnNameMap.size()) {
        throw std::exception();
    }
    relations.push_back(row);
}

void ResultTable::insertCol(std::string colName, std::vector<std::string> colValues) {
    if (colValues.size() != relations.size()) {
        throw std::exception();
    }
    columnNameMap.insert({columnNameMap.size(), colName});
    for (int i = 0; i < relations.size(); ++i) {
        relations.at(i).push_back(colValues.at(i));
    }
}

TableRow ResultTable::getColumnsNames() const {
    TableRow res(columnNameMap.size());
    for (auto const& [k, v] : columnNameMap) {
        res.at(k) = v;
    }
    return res;
}

std::unordered_set<std::string> ResultTable::getColumnsNamesSet() const {
    std::unordered_set<std::string> res;
    for (auto const& [k, v] : columnNameMap) {
        res.insert(v);
    }
    return res;
}

std::unordered_set<std::string> ResultTable::getColumnValues(std::string colName) {
    int colInt = getColumnNumber(colName);
    std::unordered_set<std::string> res;
    for (int i = 0; i < relations.size(); i++) {
        res.insert(getValueAt(i, colInt));
    }
    return res;
}

TableRow ResultTable::getColumnOrderedValues(std::string colName) {
    int colInt = getColumnNumber(colName);
    std::vector<std::string> res;
    for (int i = 0; i < relations.size(); i++) {
        res.push_back(getValueAt(i, colInt));
    }
    return res;
}

TableRow ResultTable::hasMatchingColumns(std::unordered_set<std::string> columnNamesToMatch) {
    std::vector<std::string> res;
    for (auto const& [k, v] : columnNameMap) {
        if (columnNamesToMatch.count(v)) {
            res.push_back(v);
        }
    }
    return res;
}

TableRow ResultTable::getRow(int rowNumber) const {
    return relations.at(rowNumber);
}

std::string ResultTable::getValueAt(int rowNumber, int columnNumber) const {
    return relations.at(rowNumber).at(columnNumber);
}

TableRow ResultTable::getValuesAt(int rowNumber, std::vector<int> &columnNumbers) const {
    auto row = relations.at(rowNumber);
    std::vector<std::string> res;
    for (auto col : columnNumbers) {
        res.push_back(row.at(col));
    }
    return res;
}

TableRow ResultTable::getInterestedValues(std::vector<std::string> interestedColumns) const {
    auto colNum = getColumnNumbers(interestedColumns);
    std::unordered_set<std::string> values;
    for (int i = 0; i < relations.size(); i++) {
        auto rowValue = getValuesAt(i, colNum);
        std::string s;
        std::for_each(rowValue.begin(), rowValue.end(), [&](const std::string &piece) { s += (" " + piece); });
        s.erase(0, 1);
        values.insert(s);
    }
    TableRow res;
    res.insert(res.end(), values.begin(), values.end());
    return res;
}

int ResultTable::getNumberOfRows() const {
    return relations.size();
}

TableRow ResultTable::getVectorUnion(TableRow vector1, TableRow vector2) {
    for (auto item : vector2) {
        if (std::find(vector1.begin(), vector1.end(), item) == vector1.end()) {
            vector1.push_back(item);
        }
    }
    return vector1;
}

void ResultTable::setNoResults() {
    noResults = true;
}

bool ResultTable::hasNoResults() {
    return noResults;
}

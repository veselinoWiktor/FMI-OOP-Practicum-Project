#include "DatabaseLibrary.h"
#include <filesystem> //should have C++ >= 14
namespace fs = std::filesystem;

void Database::loadDatabase(std::ifstream& ifs)
{
	String currTblPath;
	while (!ifs.eof())
	{
		ifs >> currTblPath;
		if (currTblPath == (String)"")
		{
			break;
		}
		Table currTbl((FilePath)currTblPath);
		tables.pushBack(currTbl);
	}
}

void Database::saveDatabase()
{
	String path = dbPath.getDirectory() + dbPath.getName() + dbPath.getExtension();
	std::ofstream ofs(path.c_str());
	
	int tableSize = tables.getSize();
	for (size_t i = 0; i < tableSize; i++)
	{
		ofs << (dbPath.getDirectory() + tables[i].getName() + ".ss145");
		if (i < tableSize - 1)
		{
			ofs << '\n';
		}
	}

	ofs.close();

	for (size_t i = 0; i < tables.getSize(); i++)
		saveTable(tables[i]);
}

void Database::saveTable(const Table& tbl)
{
	String path = (dbPath.getDirectory() + tbl.getName() + ".ss145");
	std::ofstream ofs(path.c_str());

	Vector<Column> columns = tbl.getColumns();
	int tblColumnCount = columns.getSize();
	ofs << tblColumnCount << '\n';

	for (size_t i = 0; i < tblColumnCount; i++)
	{
		ofs << columns[i].name << ";" << (int)columns[i].type;
		if (i < tblColumnCount - 1)
		{
			ofs << '\n';
		}
	}

	Vector<Row> rows = tbl.getRows();
	size_t rowSize = rows.getSize();

	if (rowSize != 0)
	{
		ofs << '\n';
	}

	for (size_t i = 0; i < rowSize; i++)
	{
		for (size_t j = 0; j < tblColumnCount; j++)
		{
			
			if (tblColumnCount - 1 == j)
				ofs << rows[i].getCell(j);
			else
				ofs << rows[i].getCell(j) << ";";
		}

		if (i < rowSize - 1)
			ofs << '\n';
	}
}

Database::Database(const FilePath& relativePath)
{
	if (relativePath.getExtension() != ".db")
	{
		throw std::logic_error("Database::Database(); File was not with extension .db");
	}

	String path = (relativePath.getDirectory() + relativePath.getName() + relativePath.getExtension());
	dbPath = relativePath;

	//!!!Totaly for better dynamic of the project
	//If without this to create database the directory should be created and the .db file be placed
	//and then the database would be loaded (not created) empty
	if (!fs::is_directory(relativePath.getDirectory().c_str()) || !fs::exists(relativePath.getDirectory().c_str())) { // Check if src folder exists
		fs::create_directory(relativePath.getDirectory().c_str()); // create src folder
		std::ofstream ofs(path.c_str());
		ofs.close();
	}

	std::ifstream ifs(path.c_str());
	if (!ifs.is_open())
	{
		throw std::logic_error("Database::Database(); Database file was already open!");
	}

	loadDatabase(ifs);
	ifs.close();
}

SQLResponse Database::executeQuery(const String& query)
{
	static SQLCommandFactory factory;
	SQLCommand* command = factory.createCommand(tables, query, dbPath.getName());
	SQLResponse result = command->execute();
	delete command;
	return result;
}

Database::~Database()
{
	saveDatabase();
}

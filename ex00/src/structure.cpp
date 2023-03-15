/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:00:19 by jleroux           #+#    #+#             */
/*   Updated: 2023/03/15 16:37:58 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define KV std::string, float

std::ostringstream	convert(std::string line, std::map<KV> database)
{
	std::ostringstream	os;
	std::pair<KV>		kv; //k=date, v=amount
	float				rate;

	try
	{
		kv = get_kv(line, '|');
		rate = get_rate(kv.first, database);
	}
	catch (exception &e)
	{
		return e.what();
	}

	os << kv.first << " => " << kv.second << " = " << kv.second * rate;

	return os;
}

int	main(int argc, char *argv[])
{
	std::ifstream	ifs;
	std::string		line;
	std::map<KV>	database;

	if (argc != 2)
		return err_msg("Usage: ./btc input.txt");

	input.open();
	if (!input.is_open())
		return err_msg("Failed to open " + argv[1]);

	database = load_database("data.csv");
	if (database.empty())
	{
		input.close();
		return err_msg("Failed to load database");
	}

	std::getline(file, line); //skip first line
	while (std::getline(file, line)) //for each line
		std::cout << convert(line, database) << std::endl;

	input.close();
}

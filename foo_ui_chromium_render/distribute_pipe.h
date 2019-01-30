#pragma once

class DistributePipe {
public:
	DistributePipe() = delete;
	DistributePipe(const DistributePipe &other) = delete;
	DistributePipe &operator=(const DistributePipe &other) = delete;
	~DistributePipe() = delete;

public:
	static bool connect();
	static std::string get_message_pipe_name();
	static bool disconnect();

private:
	static HANDLE pipe_handle;
};
extern "C" {
#include "prog.h"
}
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "prog.grpc.pb.h"
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using prog::logCompressSizeRequest;
using prog::logCompressSizeReply;
using prog::Prog;

class ProgServiceImpl final : public Prog::Service {
	Status logCompressSizeGrpc(ServerContext* context, const logCompressSizeRequest* request, logCompressSizeReply* reply) {
		std::cout << "start executing log Compress"<< std::endl;
		logCompressSize(request->sz());
		return Status::OK;
	}
};
void RunServer() {
	std::string server_address("0.0.0.0:50051");
	ProgServiceImpl service;
	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	server->Wait();
}
int main(int argc, char** argv) {
	RunServer();
	return 0;
}

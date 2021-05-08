#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "prog.grpc.pb.h"
#include "prog_client_stub.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using prog::logCompressSizeRequest;
using prog::logCompressSizeReply;
using prog::Prog;

class ProgClient {
	public:
	 ProgClient(std::shared_ptr<Channel> channel) : stub_(Prog::NewStub(channel)) {}
	void logCompressSizeGrpc(int sz){ 
		logCompressSizeRequest request;
		request.set_sz(sz);
		logCompressSizeReply reply;
		ClientContext context;
		Status status = stub_->logCompressSizeGrpc(&context, request, &reply);
		if (status.ok()) { 
		} else {
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
		}
	}
	private:
	 std::unique_ptr<Prog::Stub> stub_;
};

void logCompressSizeStub(int sz){
	ProgClient prog(grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials()));
	prog.logCompressSizeGrpc(sz);
}

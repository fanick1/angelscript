/**

\page doc_cpp_exceptions C++ exceptions and longjmp

\section doc_cpp_exceptions_1 Exceptions

Application functions and class methods registered with the script engine are allowed to throw C++ exceptions. The virtual machine will automatically catch any C++ exception, abort the script execution, and return control to the application.

\code
asIScriptContext *ctx = engine->CreateContext();
ctx->Prepare(engine->GetModule("test")->GetFunctionByName("func"));
int r = ctx->Execute();
if( r == asEXECUTION_EXCEPTION )
{
  string err = ctx->GetExceptionString();
  if( err == "Caught an exception from the application" )
  {
    // An application function threw an exception while being invoked from the script
    ...
  }
}
\endcode

The VM will however not be able to distinguish between different types of exceptions. If the application developer
wish to be able to do so, it will be necessary to write and register a wrapper that catches the exceptions and translates them into a script exception. 

\code
void func_wrapper()
{
  try 
  {
    func();
  }
  catch( std::exception &e )
  {
    // Tell the VM the type of exception that occurred
    asIScriptContext *ctx = asGetActiveContext();
    ctx->SetException(e.what());
  }
}
\endcode

\see \ref doc_addon_helpers "GetExceptionInfo" helper function

\note The ability to catch exceptions can be turned off by compiling the library with the AS_NO_EXCEPTIONS defined. If this is done, the application should not register any functions that may throw exceptions, as the end result will be 
undefined should an exception occur.

\section doc_cpp_exceptions_2 longjmp

Some applications uses longjmp to do error handling. When performing a longjmp to a previously saved state, there is no chance for the code to do a cleanup of all that happened after the saved state. Because of that the application must not register functions that can perform a longjmp out from the function, as that can leave the virtual machine in an undefined state.

*/

Pod::Spec.new do |s|
  s.name         = "cdebug"
  s.version      = "1.3"
  s.summary      = "Debug mode log/assertion macro for c/objc in a file."
  s.description  = <<-DESC
                    Debug log/assertion macro collections for debug mode only.
                    Append file, line, time to macro
                    * dprintf as printf/NSLog wrapper
                    * dassert as asssert wrapper
                    * dlog for conditional dprintf
                    * dassertlog for assertion after log
                    * Everythings are activated when debug mode only
                   DESC
  s.homepage     = "https://github.com/youknowone/cdebug"
  s.requires_arc = false

  s.license      = { :type => '2-clause BSD', :file => 'LICENSE' }
  s.author       = { "Jeong YunWon" => "jeong@youknowone.org" }
  s.source       = { :git => "https://github.com/youknowone/cdebug.git", :tag => s.version }

  s.static_framework = true
  s.module_name = 'debug'
  s.source_files = 'debug.h'
  s.public_header_files = 'debug.h'
end
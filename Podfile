platform :ios, '7.0'
xcodeproj 'Xcode/Awful', 'Awful Beta' => :release, 'Awful App Store' => :release
link_with 'Awful', 'Imgur API Test'
inhibit_all_warnings!

pod 'AFNetworking', '2.2.0'
pod 'GRMustache', '6.9.2'
pod 'HTMLReader', :git => "https://github.com/nolanw/HTMLReader"
pod 'JLRoutes', '1.4'
pod 'PocketAPI', '1.0.2'
pod 'PSMenuItem', '0.0.1'
pod 'SVProgressHUD', '1.0'
pod 'SVPullToRefresh', :head
pod 'WYPopoverController', '0.1.7'

target :ScrapingTests, :exclusive => true do
  pod 'HTMLReader', :git => "https://github.com/nolanw/HTMLReader"
end

# Custom text atop the "Acknowledgements" Settings screen.
class ::Pod::Generator::Acknowledgements
  def header_text
    "Awful uses these third-party libraries:"
  end
end

post_install do |i|
  plist = Xcodeproj.read_plist('Pods/Pods-acknowledgements.plist')
  licenses = plist['PreferenceSpecifiers']
  
  # Delete "generated by CocoaPods"
  licenses.delete_at(-1)
  
  # Standalone license files.
  Dir['Vendor/**/LICENSE.txt'].each do |path_to_license|
    licenses << {
      :FooterText => File.open(path_to_license).read,
      :Title => path_to_license.split(File::SEPARATOR)[1],
      :Type => "PSGroupSpecifier"
    }
  end
  
  # Licenses from header files.
  Dir['Vendor/*.h'].each do |path_to_header|
    lines = []
    File.open(path_to_header) do |header|
      header.each do |line|
        break if line[0, 2] != "//"
        lines << line[2..-1].strip
      end
    end
    licenses << {
      :FooterText => lines.join("\n"),
      :Title => File.basename(path_to_header, '.h'),
      :Type => "PSGroupSpecifier"
    }
  end
  Xcodeproj.write_plist(plist, 'Resources/Settings.bundle/Acknowledgements.plist')
end

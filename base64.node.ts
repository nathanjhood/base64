interface base64 {
  hello(): string;
  version(): string;
  encode(string: string): string;
  encode(string: string, urlMode: boolean): string;
  decode(string: string): string;
  decode(string: string, urlMode: boolean): string;
}
const base64: base64 = require('./build/lib/base64');
export = base64;

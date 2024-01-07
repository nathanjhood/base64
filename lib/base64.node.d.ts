declare interface base64 {
  hello(): string;
  version(): string;
  encode(string: string): string;
  encode(string: string, urlMode: boolean): string;
  decode(string: string): string;
  decode(string: string, urlMode: boolean): string;
}
declare const base64: base64;
export = base64;

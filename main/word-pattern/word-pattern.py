class Solution:
    def wordPattern(self, pattern, text):
        """
        :type pattern: str
        :type text: str
        :rtype: bool
        """
        words = text.split()
        if len(pattern) != len(words):
            return False

        letter_to_word = {}
        word_to_letter = {}

        for new_letter, new_word in zip(pattern, words):
            old_letter = word_to_letter.get(new_word)
            old_word = letter_to_word.get(new_letter)

            if old_letter is None and old_word is None:
                word_to_letter[new_word] = new_letter
                letter_to_word[new_letter] = new_word
            elif new_letter != old_letter or new_word != old_word:
                return False

        return True
